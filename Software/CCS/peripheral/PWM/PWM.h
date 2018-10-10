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

#include <peripheral/GPIO/GPIO.h>

typedef enum{
    PWM_0,
    PWM_1
}PWM_;

typedef enum{
    GEN_0,
    GEN_1,
    GEN_2,
    GEN_3
}PWM_GEN_;

class PWM
{
public:
    PWM();
    PWM(PWM_ PWM_, PWM_GEN_ GEN_, uint32_t freq);
    virtual ~PWM();
    void configOutPin(GPIO_PORT_ GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_P_MPWM);
    void setDutyA(float duty);
    void setDutyB(float duty);
private:
    uint32_t PWM_BASE;
    uint16_t PWM_GEN;
    uint32_t PWM_OUT_A;
    uint32_t PWM_OUT_B;
    uint32_t ulPeriod;
};

#endif /* PERIPHERAL_PWM_PWM_H_ */
