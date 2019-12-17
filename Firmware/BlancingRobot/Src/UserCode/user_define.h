/*
 * user_define.h
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_USER_DEFINE_H_
#define USERCODE_USER_DEFINE_H_

#include "tim.h"

#define TILT				0 // 0: pitch, 1: roll

#define MAX_CALLBACK_FUNC	15
#define IMU_PERIOD			5

#define MOTOR0_TIMER 	htim1
#define MOTOR1_TIMER 	htim1
#define MOTOR0_CHANNEL 	TIM_CHANNEL_4
#define MOTOR1_CHANNEL 	TIM_CHANNEL_3
#define MOTOR0_ENCODER	htim2
#define MOTOR1_ENCODER	htim3

// define if you want to change motor direction
#define MOTOR0_INVERT
#define MOTOR1_INVERT

#define MPU6050_I2C			hi2c1
#define MPU6050_ADDRESS 	(MPU6050_DEFAULT_ADDRESS << 1)

#define COM_USART			huart3
#define TX_DMA_BUF_SIZE 	512
#define RX_DMA_BUF_SIZE		512
#define TX_CIR_BUF_SIZE 	512
#define RX_CIR_BUF_SIZE 	512
#define SERIAL_PERIOD		50

#define MAV_BUFF_SIZE 				256
#define MAVLINK_CALLBACK_PERIOD		10

#define WHEEL_PERIOD				5
#define STABILITY_PERIOD			20
#define IMU_STATUS_REPORT_PERIOD	100
#define TILT_REPORT_PERIOD			100
#define CONTROLLER_PERIOD			20

#define IMU_RAW_PERIOD				50
#define ROLL_OFFSET					-6.7974

#define VX_COEFF		0.04
#define VY_COEFF		0.04
#define OMEGA_COEFF		3.0
#define THROTTLE_COEFF	5
#define WHEEL_DISTANCE	10.0

#define PARAMS_PAGE_ADDRESS 0x0800FC00
#define HAVE_SAVED_DATA		0x01

#endif /* USERCODE_USER_DEFINE_H_ */
