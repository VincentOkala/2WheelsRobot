/*
 * user_define.h
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_USER_DEFINE_H_
#define USERCODE_USER_DEFINE_H_

#include "tim.h"

#define IMU_PERIOD		10

#define MOTOR0_TIMER 	htim2
#define MOTOR1_TIMER 	htim3
#define MOTOR0_CHANNEL 	TIM_CHANNEL_3
#define MOTOR1_CHANNEL 	TIM_CHANNEL_3

// define if you want to change motor direction
//#define MOTOR0_INVERT
//#define MOTOR1_INVERT

#define MPU6050_I2C			hi2c1
#define MPU6050_ADDRESS 	(MPU6050_DEFAULT_ADDRESS << 1)

#define COM_USART			huart1
#define TX_DMA_BUF_SIZE 	512
#define RX_DMA_BUF_SIZE		512
#define TX_CIR_BUF_SIZE 	512
#define RX_CIR_BUF_SIZE 	512
#define SERIAL_PERIOD		50

#define MAV_BUFF_SIZE 			256
#define MAVLINK_CALLBACK_PERIOD	10

#define CONTROLLER_PERIOD			20
#define IMU_STATUS_REPORT_PERIOD	1000
#define RPY_REPORT_PERIOD			500

#define IMU_RAW_PERIOD			50
#define ROLL_OFFSET				-6.7974
#endif /* USERCODE_USER_DEFINE_H_ */
