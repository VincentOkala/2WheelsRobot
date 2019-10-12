/*
 * IMU.c
 *
 *  Created on: Oct 9, 2019
 *      Author: 16138
 */

#ifndef USERCODE_IMU_IMU_C_
#define USERCODE_IMU_IMU_C_

#include <math.h>
#include "IMU.h"
#include "UserCode/Params/Params.h"

static connection_failed_cb_t gconnection_failed_cb = 0;
static float roll;
static float pitch;
static timer_ID_t gtimer_ID_imu_callback;
static void imu_callback(uint8_t* ctx){
	int16_t motion_6[6];
	mpu6050_get_motion(&motion_6[0], &motion_6[1], &motion_6[2], &motion_6[3], &motion_6[4], &motion_6[5]);
	float accel_roll = atan2(motion_6[1], motion_6[2])*360/M_PI;
	float accel_pitch = atan2(motion_6[0], motion_6[2])*360/M_PI;
	float roll_rate = (motion_6[3]*250.0/32768.0)/100.0;
	float pitch_rate = (motion_6[4]*250.0/32768.0)/100.0;
	roll = params.believe_in_gyro *(roll+roll_rate) + (1-params.believe_in_gyro)*accel_roll;
	pitch = params.believe_in_gyro *(pitch+pitch_rate) + (1-params.believe_in_gyro)*accel_pitch;
}

bool IMU_init(void){
	MPU6050_init();
	mpu6050_set_full_scale_gyro_range(MPU6050_FS_SEL_250);
	mpu6050_set_full_scale_accel_range(MPU6050_AFS_SEL_2G);
	if(!MPU6050_test_connection() && gconnection_failed_cb != 0) {
		gconnection_failed_cb();
		return false;
	}
	gtimer_ID_imu_callback = timer_register_callback(imu_callback, 10, 0, TIMER_MODE_REPEAT);
	return true;
}

bool  IMU_deinit(void){
	timer_unregister_callback(gtimer_ID_imu_callback);
	return true;
}

float IMU_get_roll(void){
	return roll;
}

float IMU_get_pitch(void){
	return pitch;
}

void IMU_set_failed_cb(connection_failed_cb_t connection_failed_cb){
	gconnection_failed_cb = connection_failed_cb;
}

bool IMU_test_connection(){
	return MPU6050_test_connection();
}

#endif /* USERCODE_IMU_IMU_C_ */
