/*
 * GY521.cpp
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#include "math.h"

#include <modules/GY521/GY521.h>
#include <define.h>

GY521::GY521(){}
GY521::~GY521(){}

void GY521::init(){
    i2c = I2C(GY521_I2C, GY521_I2C_SPEED);

    GYRO_SCALE  = GY521_GYRO_SCALE;
    ACCEL_SCALE = GY521_ACCEL_SCALE;

    i2c.Write(MPU6050_ADDRESS, PWR_MGMT_1, TEMP_DIS | CLKSEL1); // Disable sleep mode, disable temperature sensor and use PLL as clock reference

    uint8_t i2cBuffer[4];
    i2cBuffer[0] = 0; // Set the sample rate to 1kHz: 1kHz/(1+0) = 1kHz
    i2cBuffer[1] = DLPF_CFG3; // Disable FSYNC and set 42 Hz Gyro filtering, set 44 Hz Accel filtering

    switch(GYRO_SCALE){
    case GYRO_SCALE_250:
        i2cBuffer[2] = FS_SEL0;
        break;
    case GYRO_SCALE_500:
        i2cBuffer[2] = FS_SEL1;
        break;
    case GYRO_SCALE_1000:
        i2cBuffer[2] = FS_SEL2;
        break;
    case GYRO_SCALE_2000:
        i2cBuffer[2] = FS_SEL3;
    }

    switch(ACCEL_SCALE){
    case ACCEL_SCALE_2G:
        i2cBuffer[3] = AFS_SEL0;
        break;
    case ACCEL_SCALE_4G:
        i2cBuffer[3] = AFS_SEL1;
        break;
    case ACCEL_SCALE_8G:
        i2cBuffer[3] = AFS_SEL2;
        break;
    case ACCEL_SCALE_16G:
        i2cBuffer[3] = AFS_SEL3;
        break;
    }

    i2cBuffer[3] = AFS_SEL3; // ACCEL_SCALE_16G
    i2c.WriteBurst(MPU6050_ADDRESS, SMPLRT_DIV, i2cBuffer, 4); // Write to all five registers at once
}

void GY521::updateAccel(){
    uint8_t buf[6];
    i2c.ReadBurst(MPU6050_ADDRESS, ACCEL_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually
    accel_raw[0] = (buf[0] << 8) | buf[1];
    accel_raw[1] = (buf[2] << 8) | buf[3];
    accel_raw[2] = (buf[4] << 8) | buf[5];
}
void GY521::updateGyro(){
    uint8_t buf[6];
    i2c.ReadBurst(MPU6050_ADDRESS, GYRO_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually
    gyro_raw[0] = (buf[0] << 8) | buf[1];
    gyro_raw[1] = (buf[2] << 8) | buf[3];
    gyro_raw[2] = (buf[4] << 8) | buf[5];
}

void GY521::getAccel(float *accel){
    updateAccel();
    accel[0] = accel_raw[0] * MPU6050AccelFactors[ACCEL_SCALE];
    accel[1] = accel_raw[1] * MPU6050AccelFactors[ACCEL_SCALE];
    accel[2] = accel_raw[2] * MPU6050AccelFactors[ACCEL_SCALE];
}

void GY521::getGyro(float *gyro){
    updateGyro();
    gyro[0] = gyro_raw[0] * MPU6050GyroFactors[GYRO_SCALE];
    gyro[1] = gyro_raw[1] * MPU6050GyroFactors[GYRO_SCALE];
    gyro[2] = gyro_raw[2] * MPU6050GyroFactors[GYRO_SCALE];
}

float GY521::getPitch(){
    updateAccel();
    return atan2(-accel_raw[0], accel_raw[2]) * RAD_TO_DEG;
}

float GY521::getRoll(){
    updateAccel();
    return atan2(accel_raw[1], accel_raw[2]) * RAD_TO_DEG;
}
