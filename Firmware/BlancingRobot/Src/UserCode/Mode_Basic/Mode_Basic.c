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

static timer_ID_t gtimer_ID_controller;
static pid_params_t pid_params = {
	.KP = 10,
	.KI = 0.1,
	.KD = 0,
	.preIPart = 0,
	.preError = 0,
	.minIpart = -500,
	.maxIPart = 500,
	.minDpart = -500,
	.maxDPart = 500,
	.minOut = -1000,
	.maxOut = 1000,
	.isFistCompute = true
};

void controller_callback(uint8_t* ctx){
	float roll = IMU_get_roll();
	float speed = pid_compute(&pid_params,roll);
	motors_setspeed(MOTOR_0, speed);
	motors_setspeed(MOTOR_1, speed);
}

void on_mode_basic_mavlink_recv(mavlink_message_t *msg){

}

void mode_basic_init(){
	motors_init();
	IMU_init();

	gtimer_ID_controller = timer_register_callback(controller_callback, CONTROLLER_PERIOD, 0, TIMER_MODE_REPEAT);
}

void mode_basic_deinit(){
	motors_setspeed(MOTOR_0, 0);
	motors_setspeed(MOTOR_1, 0);
	timer_unregister_callback(gtimer_ID_controller);
}
