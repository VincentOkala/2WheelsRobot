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
#define I2C0    0
#define I2C1    1
#define I2C2    2
#define I2C3    3

//*****************************************************************************
// The following are defines for mode of I2C modules
//*****************************************************************************
#define I2C_MODE_MASTER     0
#define I2C_MODE_SLAVE      1

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
    I2C(uint8_t ID);
    virtual ~I2C();
    bool Init(uint8_t mode, uint8_t speed);
    bool Write(uint8_t addr, uint8_t regAddr, uint8_t data);
    bool WriteBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
    bool Read(uint8_t addr, uint8_t regAddr, uint8_t *data);
    bool ReadBurst(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);

private:
    uint32_t SYSCTL_PERIPH_I2C;
    uint32_t SYSCTL_PERIPH_GPIO;

    uint32_t GPIO_PORT_BASE;
    uint32_t GPIO_PIN_SCL;
    uint32_t GPIO_PIN_SDA;

    uint32_t I2C_BASE;
    uint32_t GPIO_P_I2CSCL;
    uint32_t GPIO_P_I2CSDA;
};

#endif /* MODULES_I2C_H_ */
