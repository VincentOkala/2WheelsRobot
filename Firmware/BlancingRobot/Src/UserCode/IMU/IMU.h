/*
 * IMU.h
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_IMU_IMU_H_
#define USERCODE_IMU_IMU_H_

#include <stdbool.h>
#include "UserCode/Timer/timer.h"
#include "UserCode/IMU/MPU6050/MPU6050.h"

typedef void (*connection_failed_cb_t)(void);

bool  IMU_init(void);
bool  IMU_deinit(void);
float IMU_get_roll(void);
float IMU_get_pitch(void);
float IMU_get_tilt(void);
void IMU_get_gyro_raw(int16_t raw[3]);
void  IMU_set_failed_cb(connection_failed_cb_t connection_failed_cb);
bool IMU_test_connection();

#endif /* USERCODE_IMU_IMU_H_ */
