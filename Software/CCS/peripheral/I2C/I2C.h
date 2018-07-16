/*
 * I2C.h
 *
 *  Created on: May 8, 2018
 *      Author: light
 */

#ifndef MODULES_I2C_H_
#define MODULES_I2C_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"

//*****************************************************************************
// The following are defines for ID of I2C modules
//*****************************************************************************
#define I2C_0    0
#define I2C_1    1
#define I2C_2    2
#define I2C_3    3

//*****************************************************************************
// The following are defines for speed of I2C modules
//*****************************************************************************
#define I2C_SPEED_STANDARD  0   // 100 Kbps
#define I2C_SPEED_FAST      1   // 400 Kbps
#define I2C_SPEED_FAST_PLUS 2   // 1 Mbps
#define I2C_SPEED_HIGH      3   // 3.33 Mbps

class I2C
{
public:
    I2C();
    I2C(uint8_t I2C_, uint8_t I2C_SPEED_);
    virtual ~I2C();
    bool Write(uint8_t addr, uint8_t regAddr, uint8_t data);
    bool WriteBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
    bool Read(uint8_t addr, uint8_t regAddr, uint8_t *data);
    bool ReadBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);

private:

    uint32_t I2C_BASE;
};

#endif /* MODULES_I2C_H_ */
