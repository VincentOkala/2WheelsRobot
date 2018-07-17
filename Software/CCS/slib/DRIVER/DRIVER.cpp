/*
 * DRIVER.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#include <slib/DRIVER/DRIVER.h>
#include <slib/log/Log.h>

DRIVER::DRIVER()
{
    Log::logDoing("Initialize Driver");
    // TODO Auto-generated constructor stub
    drv8421 = DRV8412(PWM1, PWM_GEN_0, PORTD, GPIO_PIN_0, PWM_OUT_0_BIT, GPIO_PD0_M1PWM0, GPIO_PIN_1, PWM_OUT_1_BIT, GPIO_PD1_M1PWM1, PORTD, GPIO_PIN_2, GPIO_PIN_3);
    Log::logDone("Initialize Driver");
}

DRIVER::~DRIVER()
{
    // TODO Auto-generated destructor stub
}

void DRIVER::setVelocityLeft(float duty){
    duty = duty < 100 ? duty : 100;
    duty = duty > -100 ? duty : -100;
    drv8421.setVelocityLeft(duty);
}
void DRIVER::setVelocityRight(float duty){
    duty = duty < 100 ? duty : 100;
    duty = duty > -100 ? duty : -100;
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
