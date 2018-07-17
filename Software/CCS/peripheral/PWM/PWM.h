/*
 * PWM.h
 *
 *  Created on: Jun 11, 2018
 *      Author: light
 */

#ifndef PERIPHERAL_PWM_PWM_H_
#define PERIPHERAL_PWM_PWM_H_

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"

#define PWM0 0
#define PWM1 1

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

class PWM
{
public:
    PWM();
    PWM(uint8_t PWM, uint16_t PWM_GEN_, uint32_t freq);
    virtual ~PWM();
    void setOutMode(uint8_t PWM_OUT_BIT, uint8_t PORT, uint8_t GPIO_PIN_, uint32_t GPIO_P_MPWM, uint8_t duty);
    void setDuty(uint32_t PWM_OUT_, float duty);
private:
    uint32_t PWM_BASE;
    uint16_t PWM_GEN;
    uint32_t ulPeriod;
};

#endif /* PERIPHERAL_PWM_PWM_H_ */
