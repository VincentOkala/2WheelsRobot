/*
 * DRIVER.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#include <slib/Driver/Driver.h>
#include <slib/Log/Log.h>

#include <define.h>

DRIVER::DRIVER()
{
    Log::logDoing("Initialize Driver");
    drv8421 = DRV8412();
    Log::logDone("Initialize Driver");
}

DRIVER::~DRIVER()
{
    // TODO Auto-generated destructor stub
}

void DRIVER::setVelocityLeft(float duty){
    duty = duty < DRIVER_UPPER_DUTY ? duty : DRIVER_UPPER_DUTY;
    duty = duty > DRIVER_LOWER_DUTY ? duty : DRIVER_LOWER_DUTY;
    drv8421.setVelocityLeft(duty);
}
void DRIVER::setVelocityRight(float duty){
    duty = duty < DRIVER_UPPER_DUTY ? duty : DRIVER_UPPER_DUTY;
    duty = duty > DRIVER_LOWER_DUTY ? duty : DRIVER_LOWER_DUTY;
    drv8421.setVelocityRight(duty);
}

void DRIVER::disable(){
    drv8421.setVelocityLeft(0);
    drv8421.setVelocityRight(0);
    drv8421.disable();
}

void DRIVER::enable(){
    drv8421.setVelocityLeft(0);
    drv8421.setVelocityRight(0);
    drv8421.enable();
}
