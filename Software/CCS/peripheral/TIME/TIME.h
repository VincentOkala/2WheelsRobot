/*
 * TIME.h
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#ifndef PERIPHERAL_TIME_TIME_H_
#define PERIPHERAL_TIME_TIME_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"

class TIME
{
public:
    TIME();
    virtual ~TIME();
    static uint64_t tick();
    static uint32_t getTickPerUs();
    static void TIMER0_ISR();

    static uint32_t tickPerUs;

private:
    static uint32_t count;
    static uint32_t timerLoad;
};

#endif /* PERIPHERAL_TIME_TIME_H_ */
