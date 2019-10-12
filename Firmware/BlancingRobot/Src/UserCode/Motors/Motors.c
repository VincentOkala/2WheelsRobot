/*
 * Motors.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */
#include <stdlib.h>
#include "Motors.h"

#include "tim.h"
#include "gpio.h"

void motors_init(){
	HAL_TIM_PWM_Start(&MOTOR0_TIMER, MOTOR0_CHANNEL);
	HAL_TIM_PWM_Start(&MOTOR1_TIMER, MOTOR1_CHANNEL);

	__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 500);
	__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 500);

	HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_RESET);
}

void motors_deinit(){
	__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 0);
	__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 0);
	motors_setspeed(MOTOR_0, 0);
	motors_setspeed(MOTOR_1, 0);
}

void motors_setspeed(motors_t motor, int32_t speed){
	if(speed > 999) speed = 999;
	if(speed < -999) speed = -999;
	switch(motor){
	case MOTOR_0:
		if(speed == 0){
			HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_RESET);
			break;
		}
		HAL_GPIO_WritePin(MOTORS_EN0_GPIO_Port, MOTORS_EN0_Pin, GPIO_PIN_SET);
		if(speed > 0){
#ifndef MOTOR0_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(DIR0_GPIO_Port, DIR0_Pin, GPIO_PIN_RESET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(DIR0_GPIO_Port, DIR0_Pin, GPIO_PIN_SET);
#endif
		}else{
#ifndef MOTOR0_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(DIR0_GPIO_Port, DIR0_Pin, GPIO_PIN_SET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR0_TIMER, MOTOR0_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(DIR0_GPIO_Port, DIR0_Pin, GPIO_PIN_RESET);
#endif
		}
		break;
	case MOTOR_1:
		if(speed == 0){
			HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_RESET);
			break;
		}
		HAL_GPIO_WritePin(MOTORS_EN1_GPIO_Port, MOTORS_EN1_Pin, GPIO_PIN_SET);
		if(speed > 0){
#ifndef MOTOR1_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_RESET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_SET);
#endif
		}else{
#ifndef MOTOR1_INVERT
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, 1000 - abs(speed));
			HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_SET);
#else
			__HAL_TIM_SET_COMPARE(&MOTOR1_TIMER, MOTOR1_CHANNEL, abs(speed));
			HAL_GPIO_WritePin(DIR1_GPIO_Port, DIR1_Pin, GPIO_PIN_RESET);
#endif
		}
		break;
	}
}
