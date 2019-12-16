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

static timer_ID_t gtimer_ID_controller;

static void controller_callback(uint8_t* ctx){
	float tilt = IMU_get_tilt();
	float speed = pid_compute(&params.pid_params,params.stand_point-tilt);
	if(tilt > 60 || tilt < -60) {
		speed = 0;
		pid_reset(&params.pid_params);
	}
	motors_setspeed(MOTOR_0, speed);
	motors_setspeed(MOTOR_1, speed);
}

static void load_PID(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_pid_pack(0,0,&msg,params.pid_params.KP,params.pid_params.KI,params.pid_params.KD);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
	pid_reset(&params.pid_params);
}

static void save_PID(){
	// Save parameters to non-volatile memory
	params_save();

	// Respond for a successful operation
	respond_ok();
}

static void write_param(mavlink_message_t *msg){
	// Change current parameters according to GCS
	mavlink_pid_t pid;
	mavlink_msg_pid_decode(msg,&pid);
	params.pid_params.KP = pid.KP;
	params.pid_params.KI = pid.KI;
	params.pid_params.KD = pid.KD;

	pid_reset(&params.pid_params);

	// Respond for a successful operation
	respond_ok();
}

void mode_pidt_init(){
	// Hardware initialization
	motors_init();
	IMU_init();

	pid_reset(&params.pid_params);

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_pidt_deinit(){
	// Hardware de-initialization
	motors_deinit();
	IMU_deinit();

	// Periodic task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
}

void on_mode_pidt_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_PID:
		{
			mavlink_cmd_pid_t cmd_pid;
			mavlink_msg_cmd_pid_decode(msg, &cmd_pid);
			if(cmd_pid.cmd_params == CMD_LOAD) load_PID();
			else if(cmd_pid.cmd_params == CMD_SAVE) save_PID();
		}
		break;
	case MAVLINK_MSG_ID_PID:
		write_param(msg);
		break;
	default:
		break;
	}
}
