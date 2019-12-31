/*
 * PID_Tunnng.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#include <UserCode/user_define.h>

#ifdef ROBOT_MODEL_TWO_WHEELS

#include <UserCode/IMU/IMU.h>
#include <UserCode/Mode_PIDT/Mode_PIDT.h>
#include "UserCode/Motors/Motors.h"
#include <UserCode/Encoder/Encoder.h>
#include "UserCode/PID/PID.h"
#include "UserCode/Com/Com.h"
#include "UserCode/Params/Params.h"

static timer_id_t gtimer_ID_controller;
static timer_id_t gtimerid_imu_tilt;

static void controller_callback(uint8_t* ctx){
	float tilt = imu_get_tilt();

	int16_t motor0_speed = enc_read(MOTOR_0);
	int16_t motor1_speed = enc_read(MOTOR_1);
	float direction = (motor0_speed + motor1_speed)/2;

	float setpoint = (params.angle_adjusted+direction*0.05);

	float speed = pid_compute(&params.pid_sync,setpoint, tilt);
	if(tilt > 60 || tilt < -60) {
		speed = 0;
		pid_reset(&params.pid_sync);
	}
	motors_setspeed(MOTOR_0, speed);
	motors_setspeed(MOTOR_1, speed);
}

static void load_params(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	uint16_t len;

	mavlink_msg_pid_params_pack(0,0,&msg,PID_SYNC,params.pid_sync.KP,params.pid_sync.KI,params.pid_sync.KD);
	len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);

	pid_reset(&params.pid_sync);
}

static void save_params(){
	// Save parameters to non-volatile memory
	params_save();

	// Respond for a successful operation
	respond_ok();
}

static void write_param(mavlink_message_t *msg){
	// Change current parameters according to GCS
	mavlink_pid_params_t pid_msg;
	mavlink_msg_pid_params_decode(msg,&pid_msg);
	if(pid_msg.pid_control == PID_SYNC){
		params.pid_sync.KP = pid_msg.KP;
		params.pid_sync.KI = pid_msg.KI;
		params.pid_sync.KD = pid_msg.KD;

		// Respond for a successful operation
		respond_ok();
	}
}

static void tilt_report_callback(uint8_t *ctx){
	mavlink_message_t mav_msg;
	uint8_t mav_send_buf[256];
	float tilt = imu_get_tilt() - params.angle_adjusted;
	mavlink_msg_evt_tilt_pack(0,0,&mav_msg,tilt);
	uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &mav_msg);
	com_send(mav_send_buf, len);
}


void mode_pidt_init(){
	// Hardware initialization
	motors_init();
	imu_init();

	pid_reset(&params.pid_sync);

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimerid_imu_tilt = timer_register_callback(tilt_report_callback, TILT_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_pidt_deinit(){
	// Hardware de-initialization
	motors_deinit();
	imu_deinit();

	// Periodic task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
	timer_unregister_callback(gtimerid_imu_tilt);
}

void on_mode_pidt_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_PARAMS:
		{
			mavlink_cmd_params_t cmd_msg;
			mavlink_msg_cmd_params_decode(msg, &cmd_msg);
			if(cmd_msg.cmd_params == CMD_LOAD) load_params();
			else if(cmd_msg.cmd_params == CMD_SAVE) save_params();
		}
		break;
	case MAVLINK_MSG_ID_PID_PARAMS:
		write_param(msg);
		break;
	default:
		break;
	}
}

#endif
