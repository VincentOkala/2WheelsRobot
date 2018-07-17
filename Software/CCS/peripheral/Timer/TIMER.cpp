/*
 * TIME.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <peripheral/Timer/TIMER.h>
#include <stdbool.h>
#include <stdint.h>

#include <slib/LOG/LOG.h>

TIMER::TIMER(){

}

TIMER::TIMER(uint8_t TIMER_, uint16_t freq)
{
    // TODO Auto-generated constructor stub
    uint32_t SYSCTL_PERIPH_TIMER;

    switch(TIMER_){
    case TIMER_0:
        TIMER_BASE = TIMER0_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER0;
        break;
    case TIMER_1:
        TIMER_BASE = TIMER1_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER1;
        break;
    case TIMER_2:
        TIMER_BASE = TIMER2_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER2;
        break;
    case TIMER_3:
        TIMER_BASE = TIMER3_BASE;
        SYSCTL_PERIPH_TIMER = SYSCTL_PERIPH_TIMER3;
        break;
    }

    Log::logDoing("Initialize TIMER %d", TIMER_);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER);   // Enable the Timer0 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER)); // Wait for the Timer0 module to be ready.
    TimerConfigure(TIMER_BASE, TIMER_CFG_PERIODIC_UP);
    uint32_t load = SysCtlClockGet() / freq;
    TimerLoadSet(TIMER_BASE, TIMER_BOTH, load);
    TimerControlStall(TIMER_BASE, TIMER_BOTH,true); //tops counting if the processor enters debug mode;
    TimerClockSourceSet(TIMER_BASE, TIMER_CLOCK_SYSTEM);
    TimerEnable(TIMER_BASE, TIMER_BOTH);

    Log::logDone("Initialize TIMER %d", TIMER_);

}

TIMER::~TIMER()
{
    // TODO Auto-generated destructor stub
}


