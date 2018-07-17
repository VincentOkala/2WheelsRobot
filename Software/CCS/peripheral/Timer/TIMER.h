/*
 * TIME.h
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#ifndef PERIPHERAL_TIMER_TIMER_H_
#define PERIPHERAL_TIMER_TIMER_H_

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

#define TIMER_0 0
#define TIMER_1 1
#define TIMER_2 2
#define TIMER_3 3

class TIMER
{
public:
    TIMER();
    TIMER(uint8_t TIMER_, uint16_t freq);
    virtual ~TIMER();

private:
    uint32_t TIMER_BASE;
};

#endif /* PERIPHERAL_TIMER_TIMER_H_ */
