/*
 * System.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#include <slib/system/System.h>

Logger System::logger;

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
    logger = Logger();
    Log::init(&logger);
}

void System::delayMs(uint32_t time){
    SysCtlDelay(time * 30000);
}
