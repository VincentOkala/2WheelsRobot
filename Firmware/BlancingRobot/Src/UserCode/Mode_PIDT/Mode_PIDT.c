/*
 * PID_Tunnng.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */


#include <UserCode/Mode_PIDT/Mode_PIDT.h>
#include "UserCode/Motors/Motors.h"
#include "UserCode/IMU/IMU.h"
#include "UserCode/PID/PID.h"
#include "UserCode/Com/Com.h"
#include "UserCode/Params/Params.h"
#include "UserCode/Encoder/Encoder.h"

static timer_ID_t gtimer_ID_controller;
static timer_ID_t gtimer_ID_IMU_tilt;
static int32_t gspeed;

static void wheel_callback(uint8_t* ctx){
	int32_t motor0_speed = enc_read(MOTOR_0);
	int32_t motor1_speed = enc_read(MOTOR_1);
	float speed0 = pid_compute(&params.pid_whe0,gspeed - motor0_speed);
	float speed1 = pid_compute(&params.pid_whe1,gspeed - motor1_speed);
	motors_setspeed(MOTOR_0, speed0);
	motors_setspeed(MOTOR_1, speed1);
}

static void stability_callback(uint8_t* ctx){
	float tilt = IMU_get_tilt();
	gspeed= pid_compute(&params.pid_sta,params.angle_ajusted-tilt);
}

static void load_pid_params(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_pid_params_pack(0,0,&msg,
			params.pid_whe0.KP,params.pid_whe0.KI,params.pid_whe0.KD,
			params.pid_whe1.KP,params.pid_whe1.KI,params.pid_whe1.KD,
			params.pid_sta.KP,params.pid_sta.KI,params.pid_sta.KD,
			params.pid_rob.KP,params.pid_rob.KI,params.pid_rob.KD);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
	pid_reset(&params.pid_sta);
}

static void save_pid_params(){
	// Save parameters to non-volatile memory
	params_save();

	// Respond for a successful operation
	respond_ok();
}

static void write_param(mavlink_message_t *msg){
	// Change current parameters according to GCS
	mavlink_pid_params_t pid;
	mavlink_msg_pid_params_decode(msg,&pid);
	params.pid_sta.KP = pid.sta_KP;
	params.pid_sta.KI = pid.sta_KI;
	params.pid_sta.KD = pid.sta_KD;

	pid_reset(&params.pid_sta);

	// Respond for a successful operation
	respond_ok();
}

static void tilt_report_callback(uint8_t *ctx){
	mavlink_message_t tilt_msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_evt_tilt_pack(0,0,&tilt_msg,IMU_get_tilt());
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &tilt_msg);
	com_send(gmav_send_buf, len);
}

void mode_pidt_init(){
	// Hardware initialization
	motors_init();
	IMU_init();

	pid_reset(&params.pid_sta);

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(wheel_callback, WHEEL_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_controller = timer_register_callback(stability_callback, STABILITY_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_tilt = timer_register_callback(tilt_report_callback, TILT_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_pidt_deinit(){
	// Hardware de-initialization
	motors_deinit();
	IMU_deinit();

	// Periodic task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
	timer_unregister_callback(gtimer_ID_IMU_tilt);
}

void on_mode_pidt_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_PARAMS:
		{
			mavlink_cmd_params_t cmd;
			mavlink_msg_cmd_params_decode(msg, &cmd);
			if(cmd.cmd_params == CMD_LOAD) load_pid_params();
			else if(cmd.cmd_params == CMD_SAVE) save_pid_params();
		}
		break;
	case MAVLINK_MSG_ID_PID_PARAMS:
		write_param(msg);
		break;
	default:
		break;
	}
}
