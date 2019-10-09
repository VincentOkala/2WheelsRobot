/*
 * app_main.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_APP_MAIN_C_
#define USERCODE_APP_MAIN_C_

#include "app_main.h"

#include "gpio.h"
#include "tim.h"
#include "usbd_cdc_if.h"
#include "Timer/timer.h"
#include "Motors/Motors.h"
#include "IMU/IMU.h"
#include "PID/PID.h"

static float speed;
static bool run = true;

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

static void log_callback(uint8_t* ctx){
	float roll = IMU_get_roll();
	char string[30];
	sprintf(string, "%d %d\r\n", (int16_t)roll, (int16_t)speed);
	CDC_Transmit_FS((uint8_t*)string, (uint16_t)strlen(string));
}

static void controller_callback(uint8_t* ctx){
	float roll = IMU_get_roll();
	if (roll > 50 || roll < -50) run = false;
	if(run){
		speed = -pid_compute(&pid_params, roll);
		motors_setspeed(MOTOR_0, speed);
		motors_setspeed(MOTOR_1, speed);
	}
	else{
		motors_setspeed(MOTOR_0, 0);
		motors_setspeed(MOTOR_1, 0);
	}
}

void app_main(){
	HAL_Delay(1000);
	motors_init();
	IMU_init();
	timer_register_callback(log_callback, 100, 0, TIMER_MODE_REPEAT);
	timer_register_callback(controller_callback, 20, 0, TIMER_MODE_REPEAT);
}

#endif /* USERCODE_APP_MAIN_C_ */
