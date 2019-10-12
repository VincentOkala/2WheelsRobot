/*
 * Mode_Basic.c
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#include "Mode_Basic.h"
#include "UserCode/Motors/Motors.h"
#include "UserCode/IMU/IMU.h"
#include "UserCode/PID/PID.h"
#include "UserCode/Com/Com.h"
#include "UserCode/Params/Params.h"

static timer_ID_t gtimer_ID_controller;
static timer_ID_t gtimer_ID_IMU_status_report;
static timer_ID_t gtimer_ID_IMU_rpy;

static void controller_callback(uint8_t* ctx){
	float roll = IMU_get_roll();
	float speed = pid_compute(&params.pid_params,roll);
	motors_setspeed(MOTOR_0, speed);
	motors_setspeed(MOTOR_1, speed);
}

void on_mode_basic_mavlink_recv(mavlink_message_t *msg){

}

static void imu_status_report_callback(uint8_t* ctx){
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	bool connection = IMU_test_connection();
	if(connection == true) mavlink_msg_evt_sensor_status_pack(0,0,&msg,SENSOR_STATUS_IMU_OK);
	else mavlink_msg_evt_sensor_status_pack(0,0,&msg,SENSOR_STATUS_IMU_ERROR);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
}

static void rqy_report_callback(uint8_t *ctx){
	mavlink_message_t rpy_msg;
	uint8_t gmav_send_buf[256];
	float roll = IMU_get_roll();
	float pitch = IMU_get_pitch();
	mavlink_msg_evt_rpy_pack(0,0,&rpy_msg,roll,pitch);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &rpy_msg);
	com_send(gmav_send_buf, len);
}

void mode_basic_init(){
	motors_init();
	IMU_init();

	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_status_report = timer_register_callback(imu_status_report_callback, IMU_STATUS_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_rpy = timer_register_callback(rqy_report_callback, RPY_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_basic_deinit(){
	motors_deinit();
	IMU_deinit();
	timer_unregister_callback(gtimer_ID_controller);
	timer_unregister_callback(gtimer_ID_IMU_status_report);
	timer_unregister_callback(gtimer_ID_IMU_rpy);
}
