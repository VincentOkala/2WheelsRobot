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

#include <peripheral/GPIO/GPIO.h>

class DRV8412
{
public:
    DRV8412();
    virtual ~DRV8412();
    void setVelocityLeft(float duty);
    void setVelocityRight(float duty);
    void disable();
    void enable();
private:
    GPIO port;
    PWM  pwm;
};

#endif /* MODULES_DRV8412_DRV8412_H_ */
