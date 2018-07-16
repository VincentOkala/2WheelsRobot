/*
 * TIME.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <peripheral/TIME/TIME.h>

uint32_t TIME::tickPerUs = 0;
uint32_t TIME::timerLoad = 4000000000;
uint32_t TIME::count = 0;

TIME::TIME()
{
    // TODO Auto-generated constructor stub
//    timerLoad = 4*10^9;
    tickPerUs = SysCtlClockGet()/1000000;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);   // Enable the Timer0 peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)); // Wait for the Timer0 module to be ready.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, timerLoad);
    TimerControlStall(TIMER0_BASE,TIMER_BOTH,true); //tops counting if the processor enters debug mode;
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_SYSTEM);
    TimerIntRegister(TIMER0_BASE,TIMER_BOTH, TIME::TIMER0_ISR);
    TimerEnable(TIMER0_BASE, TIMER_BOTH);

}

TIME::~TIME()
{
    // TODO Auto-generated destructor stub
}

uint64_t TIME::tick(){
    return count*timerLoad + TimerValueGet(TIMER0_BASE, TIMER_A);
}
uint32_t TIME::getTickPerUs(){return tickPerUs;}

void TIME::TIMER0_ISR(){
    uint32_t flag = TimerIntStatus(TIMER0_BASE, true);
    TimerIntClear(TIMER0_BASE,flag);
    count++;
}
