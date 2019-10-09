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
#include "Motors/Motors.h"

void app_main(){
	motors_init();
	for(int32_t speed = -2000; speed < 2000; speed++){
		motors_setspeed(MOTOR_0, speed);
		motors_setspeed(MOTOR_1, speed);
		HAL_Delay(10);
	}

	motors_setspeed(MOTOR_0, 0);
	motors_setspeed(MOTOR_1, 0);
}

#endif /* USERCODE_APP_MAIN_C_ */
