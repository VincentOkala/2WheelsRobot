/*
 * System.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#include <slib/System/System.h>

Task   System::task;

System::System(){}

System::~System(){}

void System::init(){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    IntMasterEnable();  // Enable master interrupt
    task.init();
}

void System::delayMs(uint32_t time){
    SysCtlDelay(time * 20000);
}
