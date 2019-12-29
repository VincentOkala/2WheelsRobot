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
#include "UserCode/PID/PID.h"
#include "UserCode/Com/Com.h"
#include "UserCode/Params/Params.h"

static timer_id_t gtimer_ID_controller;

static void controller_callback(uint8_t* ctx){
	float tilt = imu_get_tilt();
	float speed = pid_compute(&params.pid_sync,params.angle_adjusted, tilt);
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

void mode_pidt_init(){
	// Hardware initialization
	motors_init();
	imu_init();

	pid_reset(&params.pid_sync);

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_pidt_deinit(){
	// Hardware de-initialization
	motors_deinit();
	imu_deinit();

	// Periodic task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
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
