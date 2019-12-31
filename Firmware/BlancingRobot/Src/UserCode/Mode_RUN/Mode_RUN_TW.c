/*
 * Mode_Basic.c
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#include <UserCode/user_define.h>

#ifdef ROBOT_MODEL_TWO_WHEELS

#include <UserCode/IMU/IMU.h>
#include <UserCode/Mode_RUN/Mode_RUN.h>
#include "UserCode/Motors/Motors.h"
#include "UserCode/PID/PID.h"
#include "UserCode/Com/Com.h"
#include "UserCode/Params/Params.h"

typedef struct{
	int16_t vx;
	int16_t vy;
	int16_t omega;
	uint8_t cnt;
}cmd_velocity_t;

static timer_id_t gtimerid_controller;
static timer_id_t gtimerid_imu_status_report;
static timer_id_t gtimerid_imu_tilt;

static cmd_velocity_t gcmd_velocity;

static void controller_callback(uint8_t* ctx){
	float vx=0, omega=0;

	if(gcmd_velocity.cnt == 0){
		gcmd_velocity.vx = 0;
		gcmd_velocity.omega = 0;
	}
	else{
		gcmd_velocity.cnt--;
		vx = (float)gcmd_velocity.vx;
		omega = (float)gcmd_velocity.omega;
	}

	int16_t motor0_speed = enc_read(MOTOR_0);
	int16_t motor1_speed = enc_read(MOTOR_1);
	float direction = (motor0_speed + motor1_speed)/2;

	float tilt = imu_get_tilt() - (params.angle_adjusted+direction*0.03);
	float setpoint =  (params.angle_adjusted+direction*0.03) + vx*VX_TO_TILT;
	float speed = pid_compute(&params.pid_sync,setpoint,tilt);

	if(tilt > 150 || tilt < -150) {
		speed = 0;
		pid_reset(&params.pid_sync);
	}

//	speed += vx*THROTTLE_COEFF*tilt;

	motors_setspeed(MOTOR_0, speed + omega*OMEGA_COEFF);
	motors_setspeed(MOTOR_1, speed - omega*OMEGA_COEFF);
}

static void imu_status_report_callback(uint8_t* ctx){
	mavlink_message_t msg;
	uint8_t gmav_send_buf[256];
	bool connection = imu_test_connection();
	if(connection == true) mavlink_msg_evt_sensor_pack(0,0,&msg,SENSOR_IMU_OK);
	else mavlink_msg_evt_sensor_pack(0,0,&msg,SENSOR_IMU_ERROR);
	uint16_t len = mavlink_msg_to_send_buffer(gmav_send_buf, &msg);
	com_send(gmav_send_buf, len);
}

static void tilt_report_callback(uint8_t *ctx){
	mavlink_message_t mav_msg;
	uint8_t mav_send_buf[256];
	float tilt = imu_get_tilt() - params.angle_adjusted;
	mavlink_msg_evt_tilt_pack(0,0,&mav_msg,tilt);
	uint16_t len = mavlink_msg_to_send_buffer(mav_send_buf, &mav_msg);
	com_send(mav_send_buf, len);
}


void mode_run_init(){
	// Hardware initialization
	motors_init();
	imu_init();

	// Periodic task initialization
	gtimerid_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimerid_imu_status_report = timer_register_callback(imu_status_report_callback, IMU_STATUS_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
	gtimerid_imu_tilt = timer_register_callback(tilt_report_callback, TILT_REPORT_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_run_deinit(){
	// Hardware de-initialization
	motors_deinit();
	imu_deinit();

	// Background task de-initialization
	timer_unregister_callback(gtimerid_controller);
	timer_unregister_callback(gtimerid_imu_status_report);
	timer_unregister_callback(gtimerid_imu_tilt);
}

void on_mode_run_mavlink_recv(mavlink_message_t *msg){
	switch(msg->msgid){
	case MAVLINK_MSG_ID_CMD_VELOCITY:
		{
			mavlink_cmd_velocity_t cmd_velocity;
			mavlink_msg_cmd_velocity_decode(msg, &cmd_velocity);
			gcmd_velocity.vx = cmd_velocity.v;
			gcmd_velocity.omega = cmd_velocity.omega;
			gcmd_velocity.cnt = (CONTROL_TIMEOUT_MS/CONTROLLER_PERIOD);
		}
		break;
	default:
		break;
	}
}

#endif
