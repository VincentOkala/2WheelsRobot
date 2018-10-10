/*
 * TIME.h
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#ifndef PERIPHERAL_GPTM_GPTM_H_
#define PERIPHERAL_GPTM_GPTM_H_

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

typedef enum{
    GPTM_0,
    GPTM_1,
    GPTM_2,
    GPTM_3,
    GPTM_4,
    GPTM_5,
}GPTM_;

/* Wide timer is not supported now */
class GPTM
{
public:
    GPTM();
    virtual ~GPTM();
    GPTM(GPTM_ GPTM_, uint16_t freq);
    uint32_t TIMER_BASE;
};

#endif /* PERIPHERAL_GPTM_GPTM_H_ */
