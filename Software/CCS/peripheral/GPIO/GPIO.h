/*
 * GPIO.h
 *
 *  Created on: Jun 11, 2018
 *      Author: Light
 */

#ifndef PERIPHERAL_GPIO_GPIO_H_
#define PERIPHERAL_GPIO_GPIO_H_

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

typedef enum{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F
}GPIO_PORT_;

typedef enum{
    GPIO_MODE_OUTPUT,
    GPIO_MODE_INPUT
}GPIO_MODE_;

typedef enum{
    VALUE_OFF,
    VALUE_ON,
}VALUE_;

class GPIO
{
public:
    GPIO();
    GPIO(GPIO_PORT_ GPIO_PORT_);
    virtual ~GPIO();
    void mode(uint8_t GPIO_PIN_, GPIO_MODE_ MODE_);
    void write(uint8_t GPIO_PIN_, uint8_t VALUE_);
    uint8_t read(uint8_t GPIO_PIN_);
private:
    uint32_t GPIO_PORT_BASE;
};

#endif /* PERIPHERAL_GPIO_GPIO_H_ */
