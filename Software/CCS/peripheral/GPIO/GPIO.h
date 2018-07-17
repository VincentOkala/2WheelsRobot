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

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define MODE_OUTPUT 0
#define MODE_INPUT  1

#define VALUE_OFF 0
#define VALUE_ON  1

class GPIO
{
public:
    GPIO();
    GPIO(uint8_t port);
    virtual ~GPIO();
    void write(uint8_t GPIO_PIN_, uint8_t VALUE_);
    void mode(uint8_t GPIO_PIN_, uint8_t MODE_);
private:
    uint32_t GPIO_PORT_BASE;
};

#endif /* PERIPHERAL_GPIO_GPIO_H_ */
