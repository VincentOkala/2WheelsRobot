/*
 * DRV8412.h
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#ifndef MODULES_DRV8412_DRV8412_H_
#define MODULES_DRV8412_DRV8412_H_

#include <stdint.h>
#include <stdbool.h>

#include <peripheral/GPIO/GPIO.h>
#include <peripheral/PWM/PWM.h>

#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"

class DRV8412
{
public:
    DRV8412();
    DRV8412(uint8_t PWM_, uint16_t PWM_GEN_,
            uint8_t PORT_PWM,
            uint8_t PWM_PIN_A,uint8_t PWM_OUT_BIT_A, uint32_t GPIO_P_MPWM_A,
            uint8_t PWM_PIN_B, uint8_t PWM_OUT_BIT_B, uint32_t GPIO_P_MPWM_B,
            uint8_t PORT_RST, uint8_t GPIO_PIN_RSTAB, uint8_t GPIO_PIN_RSTCD);
    virtual ~DRV8412();
    void setVelocityLeft(float duty);
    void setVelocityRight(float duty);
    void disable();
    void enable();
private:
    GPIO port;
    PWM  pwm;
    uint32_t PWM_OUT_A;
    uint32_t PWM_OUT_B;
    uint8_t  GPIO_PIN_RSTAB;
    uint8_t  GPIO_PIN_RSTCD;
};

#endif /* MODULES_DRV8412_DRV8412_H_ */
