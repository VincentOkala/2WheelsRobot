/*
 * DRV8412.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#include <modules/DRV8412/DRV8412.h>
#include <slib/Log/Log.h>

DRV8412::DRV8412(){

}

DRV8412::DRV8412(uint8_t PWM_, uint16_t PWM_GEN_,
                 uint8_t PORT_PWM,
                 uint8_t PWM_PIN_A, uint8_t PWM_OUT_BIT_A, uint32_t GPIO_P_MPWM_A,
                 uint8_t PWM_PIN_B, uint8_t PWM_OUT_BIT_B, uint32_t GPIO_P_MPWM_B,
                 uint8_t PORT_RST, uint8_t GPIO_PIN_RSTAB, uint8_t GPIO_PIN_RSTCD)
{

    Log::logDoing("Initialize DRV8412");

    this->GPIO_PIN_RSTAB = GPIO_PIN_RSTAB;
    this->GPIO_PIN_RSTCD = GPIO_PIN_RSTCD;

    // TODO Auto-generated constructor stub
    switch(PWM_OUT_BIT_A){
    case PWM_OUT_0_BIT:
        PWM_OUT_A = PWM_OUT_0;
        break;
    case PWM_OUT_1_BIT:
        PWM_OUT_A = PWM_OUT_1;
        break;
    case PWM_OUT_2_BIT:
        PWM_OUT_A = PWM_OUT_2;
        break;
    case PWM_OUT_3_BIT:
        PWM_OUT_A = PWM_OUT_3;
        break;
    case PWM_OUT_4_BIT:
        PWM_OUT_A = PWM_OUT_4;
        break;
    case PWM_OUT_5_BIT:
        PWM_OUT_A = PWM_OUT_5;
        break;
    case PWM_OUT_6_BIT:
        PWM_OUT_A = PWM_OUT_6;
        break;
    case PWM_OUT_7_BIT:
        PWM_OUT_A = PWM_OUT_7;
        break;
    }

    switch(PWM_OUT_BIT_B){
    case PWM_OUT_0_BIT:
        PWM_OUT_B = PWM_OUT_0;
        break;
    case PWM_OUT_1_BIT:
        PWM_OUT_B = PWM_OUT_1;
        break;
    case PWM_OUT_2_BIT:
        PWM_OUT_B = PWM_OUT_2;
        break;
    case PWM_OUT_3_BIT:
        PWM_OUT_B = PWM_OUT_3;
        break;
    case PWM_OUT_4_BIT:
        PWM_OUT_B = PWM_OUT_4;
        break;
    case PWM_OUT_5_BIT:
        PWM_OUT_B = PWM_OUT_5;
        break;
    case PWM_OUT_6_BIT:
        PWM_OUT_B = PWM_OUT_6;
        break;
    case PWM_OUT_7_BIT:
        PWM_OUT_B = PWM_OUT_7;
        break;
    }

    port = GPIO(PORT_RST);
    port.mode(GPIO_PIN_RSTAB, MODE_OUTPUT);
    port.mode(GPIO_PIN_RSTCD, MODE_OUTPUT);

    pwm = PWM(PWM_, PWM_GEN_, 20000);
    pwm.setOutMode(PWM_OUT_BIT_A, PORT_PWM, PWM_PIN_A, GPIO_P_MPWM_A, 50);
    pwm.setOutMode(PWM_OUT_BIT_B, PORT_PWM, PWM_PIN_B, GPIO_P_MPWM_B, 50);

    port.write(GPIO_PIN_RSTAB, VALUE_ON);
    port.write(GPIO_PIN_RSTCD, VALUE_ON);

    Log::logDone("Initialize DRV8412");

}

DRV8412::~DRV8412()
{
    // TODO Auto-generated destructor stub
}

void DRV8412::setVelocityLeft(float duty){
    duty = (duty + 100)/2;
    pwm.setDuty(PWM_OUT_A, duty);
}
void DRV8412::setVelocityRight(float duty){
    duty = (duty + 100)/2;
    pwm.setDuty(PWM_OUT_B, duty);
}

void DRV8412::disable(){
    port.write(GPIO_PIN_RSTAB, VALUE_OFF);
    port.write(GPIO_PIN_RSTCD, VALUE_OFF);
}

void DRV8412::enable(){
    port.write(GPIO_PIN_RSTAB, VALUE_ON);
    port.write(GPIO_PIN_RSTCD, VALUE_ON);
}


