/*
 * System.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#include <slib/System/System.h>

Logger System::logger;
Task   System::task;

System::System()
{
    // TODO Auto-generated constructor stub

}

System::~System()
{
    // TODO Auto-generated destructor stub
}

void System::init(){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    IntMasterEnable();  // Enable master interrupt

    logger = Logger();
    Log::init(&logger);
    task.init();
}

void System::delayMs(uint32_t time){
    SysCtlDelay(time * 20000);
}
