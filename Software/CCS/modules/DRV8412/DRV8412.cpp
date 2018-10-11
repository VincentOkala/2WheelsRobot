/*
 * DRV8412.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#include <define.h>
#include <modules/DRV8412/DRV8412.h>
#include <slib/Log/Log.h>


DRV8412::DRV8412(){}
DRV8412::~DRV8412(){}

void DRV8412::init(){
    pwm = PWM(DRV8421_PWM, DRV8421_PWM_GEN, DRV8421_PWM_FREQ);
    pwm.setDutyA(50);
    pwm.setDutyB(50);
    pwm.configOutPin(DRV8421_PWM_PORT, DRV8421_PIN_A, DRV8421_MPWM_A);
    pwm.configOutPin(DRV8421_PWM_PORT, DRV8421_PIN_B, DRV8421_MPWM_B);

    port = GPIO(DRV8421_PORT_RST);
    port.mode(DRV8421_RSTAB_PIN, GPIO_MODE_OUTPUT);
    port.mode(DRV8421_RSTCD_PIN, GPIO_MODE_OUTPUT);


    port.write(DRV8421_RSTAB_PIN, VALUE_OFF);
    port.write(DRV8421_RSTCD_PIN, VALUE_OFF);
}

void DRV8412::setVelocityLeft(float duty){

    duty = (duty + 100)/2; // convert from -100--100 to 0--100

    duty = duty > DRV8421_UPPER_DUTY ? DRV8421_UPPER_DUTY : duty;
    duty = duty < DRV8421_LOWER_DUTY ? DRV8421_UPPER_DUTY : duty;

    pwm.setDutyA(duty);
}
void DRV8412::setVelocityRight(float duty){

    duty = (duty + 100)/2; // convert from -100--100 to 0--100

    duty = duty > DRV8421_UPPER_DUTY ? DRV8421_UPPER_DUTY : duty;
    duty = duty < DRV8421_LOWER_DUTY ? DRV8421_UPPER_DUTY : duty;

    pwm.setDutyB(duty);
}

void DRV8412::disable(){
    port.write(DRV8421_RSTAB_PIN, VALUE_OFF);
    port.write(DRV8421_RSTCD_PIN, VALUE_OFF);
}

void DRV8412::enable(){
    port.write(DRV8421_RSTAB_PIN, VALUE_ON);
    port.write(DRV8421_RSTCD_PIN, VALUE_ON);
}


