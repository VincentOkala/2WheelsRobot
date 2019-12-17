/*
 * Encoder.c
 *
 *  Created on: Dec 17, 2019
 *      Author: 16138
 */

#include "Encoder.h"
#include "UserCode/Timer/timer.h"
#include "tim.h"
#include "UserCode/user_define.h"

void enc_init(){
	HAL_TIM_Encoder_Start(&MOTOR0_ENCODER,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&MOTOR1_ENCODER,TIM_CHANNEL_ALL);
	MOTOR0_ENCODER.Instance->CNT = 0;
	MOTOR1_ENCODER.Instance->CNT = 0;
}

int32_t enc_read(motors_t motor){
	int32_t enc = 0;
	switch(motor){
	case MOTOR_0:
		enc = MOTOR0_ENCODER.Instance->CNT;
		MOTOR0_ENCODER.Instance->CNT = 0;
		break;
	case MOTOR_1:
		enc = MOTOR1_ENCODER.Instance->CNT;
		MOTOR1_ENCODER.Instance->CNT = 0;
		break;
	}
	return enc;
}
