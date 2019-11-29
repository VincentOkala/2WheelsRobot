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
	float tilt = IMU_get_tilt();
	mavlink_msg_evt_gyro_raw_pack(0,0,&imu_raw_msg,raw[0],raw[1],raw[2], tilt);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &imu_raw_msg);
	com_send(gmav_send_buf, len);
}

static void load_gyro_offset(){
	// Load parameters from non-volatile memory
	params_load();

	// Send parameters to GCS
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_gyro_offset_pack(0,0,&msg, params.gx_offset, params.gy_offset, params.gz_offset, params.stand_point);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
}

static void save_gyro_offset(){
	// Save parameters to non-volatile memory
	params_save();

	// Respond a successful operation
	respond_ok();
}

static void write_param(mavlink_message_t *msg){
	// Change current parameters according to GCS
	mavlink_gyro_offset_t gyro_offset;
	mavlink_msg_gyro_offset_decode(msg,&gyro_offset);
	params.gx_offset = gyro_offset.gyro_offet_x;
	params.gy_offset = gyro_offset.gyro_offet_y;
	params.gz_offset = gyro_offset.gyro_offet_z;
	params.stand_point = gyro_offset.stand_point;

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
	case MAVLINK_MSG_ID_CMD_GYRO_OFFSET:
		{
			mavlink_cmd_gyro_offset_t cmd_gyro_offet;
			mavlink_msg_cmd_gyro_offset_decode(msg, &cmd_gyro_offet);
			if(cmd_gyro_offet.cmd_params == CMD_LOAD) load_gyro_offset();
			else if(cmd_gyro_offet.cmd_params == CMD_SAVE) save_gyro_offset();
		}
		break;
	case MAVLINK_MSG_ID_GYRO_OFFSET:
		write_param(msg);
		break;
	default:
		break;
	}
}
