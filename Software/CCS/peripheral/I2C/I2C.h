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

typedef enum{
    I2C_0,
    I2C_1,
    I2C_2,
    I2C_3
}I2C_;

typedef enum{
    I2C_SPEED_STANDARD,     // 100 Kbps
    I2C_SPEED_FAST,         // 400 Kbps
    I2C_SPEED_FAST_PLUS,    // 1 Mbps
    I2C_SPEED_HIGH          // 3.33 Mbps
}I2C_SPEED_;

class I2C
{
public:
    I2C();
    I2C(I2C_ I2C_, I2C_SPEED_ I2C_SPEED_);
    virtual ~I2C();

    void Write(uint8_t addr, uint8_t data);
    void WriteBurst(uint8_t addr, uint8_t *data, uint8_t length);

    void Write(uint8_t addr, uint8_t regAddr, uint8_t data);
    void WriteBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
    void Read(uint8_t addr, uint8_t regAddr, uint8_t *data);
    void ReadBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);

private:
    uint32_t I2C_BASE;
};

#endif /* MODULES_I2C_H_ */
