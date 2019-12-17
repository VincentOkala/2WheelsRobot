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

typedef struct{
	int16_t v;
	int16_t omega;
	uint8_t cnt;
}cmd_velocity_t;

static timer_ID_t gtimer_ID_controller;
static timer_ID_t gtimer_ID_IMU_status_report;
static timer_ID_t gtimer_ID_IMU_tilt;
static cmd_velocity_t gcmd_velocity;

static void controller_callback(uint8_t* ctx){
	float vx=0, omega=0;

	if(gcmd_velocity.cnt == 0){
		gcmd_velocity.v = 0;
		gcmd_velocity.omega = 0;
	}
	else{
		gcmd_velocity.cnt--;
		vx = (float)gcmd_velocity.v;
		omega = (float)gcmd_velocity.omega;
	}

	float tilt = IMU_get_tilt();
	float setpoint = params.angle_ajusted - vx*VX_COEFF;
	float speed = pid_compute(&params.pid_sta,setpoint - tilt);

	if(tilt > 150 || tilt < -150) {
		speed = 0;
		pid_reset(&params.pid_sta);
	}

	speed -= vx*THROTTLE_COEFF;

	motors_setspeed(MOTOR_0, speed - omega*OMEGA_COEFF);
	motors_setspeed(MOTOR_1, speed + omega*OMEGA_COEFF);
}

static void imu_status_report_callback(uint8_t* ctx){
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	bool connection = IMU_test_connection();
	if(connection == true) mavlink_msg_evt_sensor_pack(0,0,&msg,SENSOR_IMU_OK);
	else mavlink_msg_evt_sensor_pack(0,0,&msg,SENSOR_IMU_ERROR);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
}

static void tilt_report_callback(uint8_t *ctx){
	mavlink_message_t tilt_msg;
	uint8_t gmav_send_buf[256];
	mavlink_msg_evt_tilt_pack(0,0,&tilt_msg,IMU_get_tilt());
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &tilt_msg);
	com_send(gmav_send_buf, len);
}

void mode_basic_init(){
	// Hardware initialization
	motors_init();
	IMU_init();

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_status_report = timer_register_callback(imu_status_report_callback, IMU_STATUS_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_tilt = timer_register_callback(tilt_report_callback, TILT_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_basic_deinit(){
	// Hardware de-initialization
	motors_deinit();
	IMU_deinit();

	// Background task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
	timer_unregister_callback(gtimer_ID_IMU_status_report);
	timer_unregister_callback(gtimer_ID_IMU_tilt);
}

void on_mode_basic_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_VELOCITY:
		{
			mavlink_cmd_velocity_t cmd_velocity;
			mavlink_msg_cmd_velocity_decode(msg, &cmd_velocity);
			gcmd_velocity.v = cmd_velocity.v;
			gcmd_velocity.omega = cmd_velocity.omega;
			gcmd_velocity.cnt = 50; // 1s timeout
		}
		break;
	default:
		break;
	}
}
