/*
 * DRIVER.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#include <slib/Driver/Driver.h>

#include <define.h>

Driver::Driver(){}
Driver::~Driver(){}

DRV8412 Driver::drv8421;

void Driver::init(){
    drv8421.init();
}

void Driver::setVelocityLeft(float duty){
    duty = duty < DRIVER_UPPER_DUTY ? duty : DRIVER_UPPER_DUTY;
    duty = duty > DRIVER_LOWER_DUTY ? duty : DRIVER_LOWER_DUTY;
    drv8421.setVelocityLeft(duty);
}
void Driver::setVelocityRight(float duty){
    duty = duty < DRIVER_UPPER_DUTY ? duty : DRIVER_UPPER_DUTY;
    duty = duty > DRIVER_LOWER_DUTY ? duty : DRIVER_LOWER_DUTY;
    drv8421.setVelocityRight(duty);
}

void Driver::disable(){
    drv8421.setVelocityLeft(0);
    drv8421.setVelocityRight(0);
    drv8421.disable();
}

void Driver::enable(){
    drv8421.setVelocityLeft(0);
    drv8421.setVelocityRight(0);
    drv8421.enable();
}
