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
	int16_t vx;
	int16_t vy;
	int16_t omega;
	uint8_t cnt;
}cmd_velocity_t;

static timer_id_t gtimer_ID_controller;
static timer_id_t gtimer_ID_IMU_status_report;
static timer_id_t gtimer_ID_IMU_rpy;
static cmd_velocity_t gcmd_velocity;

static void controller_callback(uint8_t* ctx){
	float vx=0, omega=0;

	if(gcmd_velocity.cnt == 0){
		gcmd_velocity.vx = 0;
//		gcmd_velocity.vy = 0;
		gcmd_velocity.omega = 0;
	}
	else{
		gcmd_velocity.cnt--;
		vx = (float)gcmd_velocity.vx;
//		vy = gcmd_velocity.vy*VY_MAX/100.0;
		omega = (float)gcmd_velocity.omega;
	}

	float tilt = IMU_get_tilt();
	float setpoint = params.angle_ajusted - vx*VX_COEFF;
	float speed = pid_compute(&params.pid_sync,setpoint,tilt);

	if(tilt > 150 || tilt < -150) {
		speed = 0;
		pid_reset(&params.pid_sync);
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

static void rqy_report_callback(uint8_t *ctx){
	mavlink_message_t rpy_msg;
	uint8_t gmav_send_buf[256];
	float roll = IMU_get_roll();
	float pitch = IMU_get_pitch();
	float yaw = IMU_get_yaw();
	mavlink_msg_evt_rpy_pack(0,0,&rpy_msg,roll,pitch,yaw);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &rpy_msg);
	com_send(gmav_send_buf, len);
}

void mode_basic_init(){
	// Hardware initialization
	motors_init();
	IMU_init();

	// Periodic task initialization
	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_status_report = timer_register_callback(imu_status_report_callback, IMU_STATUS_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimer_ID_IMU_rpy = timer_register_callback(rqy_report_callback, RPY_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_basic_deinit(){
	// Hardware de-initialization
	motors_deinit();
	IMU_deinit();

	// Background task de-initialization
	timer_unregister_callback(gtimer_ID_controller);
	timer_unregister_callback(gtimer_ID_IMU_status_report);
	timer_unregister_callback(gtimer_ID_IMU_rpy);
}

void on_mode_basic_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_VELOCITY:
		{
			mavlink_cmd_velocity_t cmd_velocity;
			mavlink_msg_cmd_velocity_decode(msg, &cmd_velocity);
			gcmd_velocity.vx = cmd_velocity.v;
			gcmd_velocity.omega = cmd_velocity.omega;
			gcmd_velocity.cnt = 50; // 1s timeout
		}
		break;
	default:
		break;
	}
}
