/*
 * hardware_define.h
 *
 *  Created on: Sep 25, 2018
 *      Author: 16138
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include <peripheral/GPIO/GPIO.h>
#include <peripheral/PWM/PWM.h>
#include <peripheral/I2C/I2C.h>

/* DRV8421 */
#define DRV8421_PWM                 PWM_1
#define DRV8421_PWM_GEN             GEN_0
#define DRV8421_PWM_FREQ            20000

#define DRV8421_PWM_PORT            GPIO_PORT_D
#define DRV8421_PIN_A               GPIO_PIN_0
#define DRV8421_MPWM_A              GPIO_PD0_M1PWM0
#define DRV8421_PIN_B               GPIO_PIN_1
#define DRV8421_MPWM_B              GPIO_PD1_M1PWM1

#define DRV8421_PORT_RST            GPIO_PORT_D
#define DRV8421_RSTAB_PIN           GPIO_PIN_2
#define DRV8421_RSTCD_PIN           GPIO_PIN_3

#define DRV8421_UPPER_DUTY          98
#define DRV8421_LOWER_DUTY          2

#define DRIVER_UPPER_DUTY           100
#define DRIVER_LOWER_DUTY           -100

/* GY521 */
#define GY521_I2C                   I2C_1
#define GY521_I2C_SPEED             I2C_SPEED_STANDARD
#define GY521_GYRO_SCALE            GYRO_SCALE_250
#define GY521_ACCEL_SCALE           ACCEL_SCALE_2G

/* ESP8266 */
#define ESP8266_UART                UART_1
#define ESP8266_UART_BAUD           115200

/* CC1101 */
#define CC1101_UART                 UART_2
#define CC1101_UART_BAUD            115200

#endif /* DEFINE_H_ */
