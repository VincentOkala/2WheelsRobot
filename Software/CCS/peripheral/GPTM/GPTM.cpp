/*
 * TIME.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <peripheral/GPTM/GPTM.h>
#include <slib/Log/Log.h>
#include <stdbool.h>
#include <stdint.h>


GPTM::GPTM(){}
GPTM::~GPTM(){}

/**
 * @brief Construct a new GPTM::GPTM object
 * 
 * @param GPTM_ GPTM_0 --> GPTM_5
 * @param freq 0.02 --> SysCtlClockGet() Hz
 */
GPTM::GPTM(GPTM_ GPTM_, uint16_t freq)
{
    uint32_t SYSCTL_PERIPH_TIMER;

    switch(GPTM_){
    case GPTM_0:
        TIMER_BASE = TIMER0_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER0;
        break;
    case GPTM_1:
        TIMER_BASE = TIMER1_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER1;
        break;
    case GPTM_2:
        TIMER_BASE = TIMER2_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER2;
        break;
    case GPTM_3:
        TIMER_BASE = TIMER3_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER3;
        break;
    case GPTM_4:
        TIMER_BASE = TIMER4_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER4;
        break;
    case GPTM_5:
        TIMER_BASE = TIMER5_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER5;
        break;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER);   // Enable the Timer peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER)); // Wait for the Timer module to be ready.

    TimerConfigure(TIMER_BASE, TIMER_CFG_PERIODIC_UP);
    uint32_t load = SysCtlClockGet() / freq;
    TimerLoadSet(TIMER_BASE, TIMER_BOTH, load);
    TimerControlStall(TIMER_BASE, TIMER_BOTH,true); //tops counting if the processor enters debug mode;
    TimerClockSourceSet(TIMER_BASE, TIMER_CLOCK_SYSTEM);
    TimerEnable(TIMER_BASE, TIMER_BOTH);
}


