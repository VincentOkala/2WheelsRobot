/*
 * MPU6050_REGISTER_MAP.h
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "../../slib/Bit.h"

#define SELF_TEST_X      0x0D
#define SELF_TEST_Y      0x0E
#define SELF_TEST_Z      0x0F
#define SELF_TEST_A      0x10
#define SMPLRT_DIV       0x19
#define CONFIG           0x1A
#define GYRO_CONFIG      0x1B
#define ACCEL_CONFIG     0x1C
#define FIFO_EN          0x23
#define I2C_MST_CTRL     0x24
#define I2C_SLV0_ADDR    0x25
#define I2C_SLV0_REG     0x26
#define I2C_SLV0_CTRL    0x27
#define I2C_SLV1_ADDR    0x28
#define I2C_SLV1_REG     0x29
#define I2C_SLV1_CTRL    0x2A
#define I2C_SLV2_ADDR    0x2B
#define I2C_SLV2_REG     0x2C
#define I2C_SLV2_CTRL    0x2D
#define I2C_SLV3_ADDR    0x2E
#define I2C_SLV3_REG     0x2F
#define I2C_SLV3_CTRL    0x30
#define I2C_SLV4_ADDR    0x31
#define I2C_SLV4_REG     0x32
#define I2C_SLV4_DO      0x33
#define I2C_SLV4_CTRL    0x34
#define I2C_SLV4_DI      0x35
#define I2C_MST_STATUS   0x36
#define INT_PIN_CFG      0x37
#define INT_ENABLE       0x38
#define INT_STATUS       0x3A
#define ACCEL_XOUT_H     0x3B
#define ACCEL_XOUT_L     0x3C
#define ACCEL_YOUT_H     0x3D
#define ACCEL_YOUT_L     0x3E
#define ACCEL_ZOUT_H     0x3F
#define ACCEL_ZOUT_L     0x40
#define TEMP_OUT_H       0x41
#define TEMP_OUT_L       0x42
#define GYRO_XOUT_H      0x43
#define GYRO_XOUT_L      0x44
#define GYRO_YOUT_H      0x45
#define GYRO_YOUT_L      0x46
#define GYRO_ZOUT_H      0x47
#define GYRO_ZOUT_L      0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define I2C_SLV0_DO      0x63
#define I2C_SLV1_DO      0x64
#define I2C_SLV2_DO      0x65
#define I2C_SLV3_DO      0x66
#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET  0x68
#define USER_CTRL        0x6A
#define PWR_MGMT_1       0x6B
#define PWR_MGMT_2       0x6C
#define FIFO_COUNTH      0x72
#define FIFO_COUNTL      0x73
#define FIFO_R_W         0x74
#define WHO_AM_I         0x75 // Should return 0x68

/* PWR_MGMT_1 */
#define DEVICE_RESET    BIT7
#define SLEEP           BIT6
#define CYCLE           BIT5
#define TEMP_DIS        BIT3            // disable temperature sensor
#define CLKSEL0         0
#define CLKSEL1         (BIT0)
#define CLKSEL2         (BIT1)
#define CLKSEL3         (BIT1 + BIT0)
#define CLKSEL4         (BIT2)
#define CLKSEL5         (BIT2 + BIT0)
#define CLKSEL6         (BIT2 + BIT1)
#define CLKSEL7         (BIT2 + BIT1 + BIT0)

/* CONFIG */
#define EXT_SYNC_SET0   0
#define EXT_SYNC_SET1   (BIT3)
#define EXT_SYNC_SET2   (BIT4)
#define EXT_SYNC_SET3   (BIT4 + BIT3)
#define EXT_SYNC_SET4   (BIT5)
#define EXT_SYNC_SET5   (BIT5 + BIT3)
#define EXT_SYNC_SET6   (BIT5 + BIT4)
#define EXT_SYNC_SET7   (BIT5 + BIT4 + BIT3)
#define DLPF_CFG0       0
#define DLPF_CFG1       (BIT0)
#define DLPF_CFG2       (BIT1)
#define DLPF_CFG3       (BIT1 + BIT0)
#define DLPF_CFG4       (BIT2)
#define DLPF_CFG5       (BIT2 + BIT0)
#define DLPF_CFG6       (BIT2 + BIT1)
#define DLPF_CFG7       (BIT2 + BIT1 + BIT0)

/* GYRO_CONFIG */
#define XG_ST           BIT7
#define YG_ST           BIT6
#define ZG_ST           BIT5
#define FS_SEL0         0               // ± 250 °/s
#define FS_SEL1         (BIT3)          // ± 500 °/s
#define FS_SEL2         (BIT4)          // ± 1000 °/s
#define FS_SEL3         (BIT4 + BIT3)   // ± 2000 °/s

/* ACCEL_CONFIG */
#define XA_ST           BIT7
#define YA_ST           BIT6
#define ZA_ST           BIT5
#define AFS_SEL0        0               // ± 2g
#define AFS_SEL1        (BIT3)          // ± 4g
#define AFS_SEL2        (BIT4)          // ± 8g
#define AFS_SEL3        (BIT4 + BIT3)   // ± 16g

/* FIFO_EN */
#define TEMP_FIFO_EN    BIT7
#define XG_FIFO_EN      BIT6
#define YG_FIFO_EN      BIT5
#define ZG_FIFO_EN      BIT4
#define ACCEL_FIFO_EN   BIT3
#define SLV2_FIFO_EN    BIT2
#define SLV1_FIFO_EN    BIT1
#define SLV0_FIFO_EN    BIT0

//*****************************************************************************
// The factors used to convert the acceleration readings from the MPU6050 into
// floating point values in meters per second squared.
// Values are obtained by taking the g conversion factors from the data sheet
// and multiplying by 9.81 (1 g = 9.81 m/s^2).
//*****************************************************************************
static const float MPU6050AccelFactors[] =
{
    0.00059875,                              // Range = +/- 2 g (16384 lsb/g)
    0.00119751,                              // Range = +/- 4 g (8192 lsb/g)
    0.00239502,                              // Range = +/- 8 g (4096 lsb/g)
    0.00479004                               // Range = +/- 16 g (2048 lsb/g)
};

//*****************************************************************************
// The factors used to convert the acceleration readings from the MPU6050 into
// floating point values in radians per second.
// Values are obtained by taking the degree per second conversion factors
// from the data sheet and then converting to radians per sec (1 degree =
// 0.0174532925 radians).
//*****************************************************************************
static const float MPU6050GyroFactors[] =
{
    1.3323124e-4f,   // Range = +/- 250 dps  (131.0 LSBs/DPS)
    2.6646248e-4f,   // Range = +/- 500 dps  (65.5 LSBs/DPS)
    5.3211258e-4f,   // Range = +/- 1000 dps (32.8 LSBs/DPS)
    0.0010642252f    // Range = +/- 2000 dps (16.4 LSBs/DPS)
};

#endif /* MPU6050_MPU6050_REGISTER_MAP_H_ */
