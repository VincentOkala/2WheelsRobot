/*
 * Mode_IMU.c
 *
 *  Created on: Oct 13, 2019
 *      Author: 16138
 */

#include "Mode_IMU.h"
#include "UserCode/Params/Params.h"
#include "UserCode/Timer/timer.h"
#include "UserCode/IMU/IMU.h"
#include "UserCode/Com/Com.h"

static timer_ID_t gtimer_ID_IMU_Raw;

static void imu_raw_callback(uint8_t* ctx){
	mavlink_message_t imu_raw_msg;
	uint8_t gmav_send_buf[256];
	int16_t raw[3];
	IMU_get_gyro_raw(raw);
	float roll = IMU_get_roll();
	mavlink_msg_evt_imu_raw_pack(0,0,&imu_raw_msg,raw[0],raw[1],raw[2], roll);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &imu_raw_msg);
	com_send(gmav_send_buf, len);
}

static void load_imu_params(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_imu_params_pack(0,0,&msg, params.gx_offset, params.gy_offset, params.gz_offset,
			params.angle_ajusted, params.believe_in_gyro);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
}

static void save_imu_params(){
	// Save parameters to non-volatile memory
	params_save();

	// Respond a successful operation
	respond_ok();
}

static void write_imu_params(mavlink_message_t *msg){
	// Change current parameters according to GCS
	mavlink_imu_params_t imu_params;
	mavlink_msg_imu_params_decode(msg,&imu_params);
	params.gx_offset = imu_params.gyro_offet_x;
	params.gy_offset = imu_params.gyro_offet_y;
	params.gz_offset = imu_params.gyro_offet_z;
	params.angle_ajusted = imu_params.angle_ajusted;
	params.believe_in_gyro = imu_params.believe_in_gyro;

	// Respond a successful operation
	respond_ok();
}

void mode_imu_init(){
	// Hardware initialization
	IMU_init();

	// Periodic task initialization
	gtimer_ID_IMU_Raw = timer_register_callback(imu_raw_callback, IMU_RAW_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_imu_deinit(){
	// Hardware de-initialization
	IMU_deinit();

	// Periodic task initialization
	timer_unregister_callback(gtimer_ID_IMU_Raw);
}

void on_mode_imu_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_PARAMS:
		{
			mavlink_cmd_params_t cmd;
			mavlink_msg_cmd_params_decode(msg, &cmd);
			if(cmd.cmd_params == CMD_LOAD) load_imu_params();
			else if(cmd.cmd_params == CMD_SAVE) save_imu_params();
		}
		break;
	case MAVLINK_MSG_ID_IMU_PARAMS:
		write_imu_params(msg);
		break;
	default:
		break;
	}
}
