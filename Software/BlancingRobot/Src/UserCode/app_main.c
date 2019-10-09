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

char string[30];
static void imu_callback(uint8_t* ctx){
	float roll = IMU_get_roll();
	float pitch = IMU_get_pitch();
	sprintf(string, "%d %d\r\n", (int16_t)roll, (int16_t)pitch);
	CDC_Transmit_FS((uint8_t*)string, (uint16_t)strlen(string));
}

bool connection_OK;
void app_main(){
	HAL_Delay(1000);
//	motors_init();
//	for(int32_t speed = -2000; speed < 2000; speed++){
//		motors_setspeed(MOTOR_0, speed);
//		motors_setspeed(MOTOR_1, speed);
//		HAL_Delay(5);
//	}
//
//	motors_setspeed(MOTOR_0, 0);
//	motors_setspeed(MOTOR_1, 0);
	IMU_init();
	timer_register_callback(imu_callback, 100, 0, TIMER_MODE_REPEAT);
}

#endif /* USERCODE_APP_MAIN_C_ */
