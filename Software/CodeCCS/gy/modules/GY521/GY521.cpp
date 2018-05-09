/*
 * GY521.cpp
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#include "GY521.h"
#include "math.h"

GY521::GY521()
{
   // TODO Auto-generated constructor stub
}
GY521::GY521(uint8_t I2CID){
    i2c = I2C(I2CID);
}
GY521::~GY521()
{
    // TODO Auto-generated destructor stub
}

bool GY521::Init(){
    GYRO_SCALE = GYRO_SCALE_2000;
    ACCEL_SCALE = ACCEL_SCALE_16G;

    i2c.Init(I2C_MODE_MASTER, I2C_SPEED_STANDARD);

//    uint8_t reset = DEVICE_RESET;
//    i2c.Write(MPU6050_ADDRESS, PWR_MGMT_1,  DEVICE_RESET); // Reset device, this resets all internal registers to their default values
//    SysCtlDelay(100);
//    while(reset & DEVICE_RESET){
//        i2c.Read(MPU6050_ADDRESS, PWR_MGMT_1, &reset);
//    }
//    i2c.Read(MPU6050_ADDRESS, PWR_MGMT_1, &reset);

    i2c.Write(MPU6050_ADDRESS, PWR_MGMT_1, TEMP_DIS | CLKSEL1); // Disable sleep mode, disable temperature sensor and use PLL as clock reference

    uint8_t i2cBuffer[4];
    i2cBuffer[0] = 0; // Set the sample rate to 1kHz: 1kHz/(1+0) = 1kHz
    i2cBuffer[1] = DLPF_CFG3; // Disable FSYNC and set 42 Hz Gyro filtering, set 44 Hz Accel filtering
    i2cBuffer[2] = FS_SEL3;  // GYRO_SCALE_2000
    i2cBuffer[3] = AFS_SEL3; // ACCEL_SCALE_16G
    i2c.WriteBurst(MPU6050_ADDRESS, SMPLRT_DIV, i2cBuffer, 4); // Write to all five registers at once

//    i2cBuffer[0] = (1 << 5) | (1 << 4); // Enable LATCH_INT_EN and INT_ANYRD_2CLEAR
//    // When this bit is equal to 1, the INT pin is held high until the interrupt is cleared
//    // When this bit is equal to 1, interrupt status is cleared if any read operation is performed
//    i2cBuffer[1] = (1 << 0);            // Enable RAW_RDY_EN - When set to 1, Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin
//    i2c.WriteBurst(MPU6050_ADDRESS, INT_PIN_CFG, i2cBuffer, 2); // Write to both registers at once
//    SysCtlDelay(200);

    return true;
}

bool GY521::Init(uint8_t gyroScale, uint8_t accelScale){
    GYRO_SCALE  = gyroScale;
    ACCEL_SCALE = accelScale;

    i2c.Init(I2C_MODE_MASTER, I2C_SPEED_STANDARD);
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

    return true;
}

bool GY521::getAccel(float *accel){
    uint8_t buf[6];
    i2c.ReadBurst(MPU6050_ADDRESS, ACCEL_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually
    accel_raw[0] = (buf[0] << 8) | buf[1];
    accel_raw[1] = (buf[2] << 8) | buf[3];
    accel_raw[2] = (buf[4] << 8) | buf[5];
    accel[0] = accel_raw[0] * MPU6050AccelFactors[ACCEL_SCALE];
    accel[1] = accel_raw[1] * MPU6050AccelFactors[ACCEL_SCALE];
    accel[2] = accel_raw[2] * MPU6050AccelFactors[ACCEL_SCALE];
    return true;
}
bool GY521::getGyro(float *gyro){
    uint8_t buf[6];
    i2c.ReadBurst(MPU6050_ADDRESS, GYRO_XOUT_H, buf, 6); // Note that we can't write directly into MPU6050_t, because of endian conflict. So it has to be done manually
    gyro_raw[0] = (buf[0] << 8) | buf[1];
    gyro_raw[1] = (buf[2] << 8) | buf[3];
    gyro_raw[2] = (buf[4] << 8) | buf[5];
    gyro[0] = gyro_raw[0] * MPU6050GyroFactors[GYRO_SCALE];
    gyro[1] = gyro_raw[1] * MPU6050GyroFactors[GYRO_SCALE];
    gyro[2] = gyro_raw[2] * MPU6050GyroFactors[GYRO_SCALE];
    return true;
}

bool GY521::getPitch(float *pitch){
    *pitch =  atan2(-accel_raw[0], accel_raw[2]) * RAD_TO_DEG;
    return true;
}
bool GY521::getRoll(float *roll){
    *roll =  atan2(accel_raw[1], accel_raw[2]) * RAD_TO_DEG;
    return true;
}
