/*
 * PWM.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: light
 */

#include <peripheral/PWM/PWM.h>
#include <slib/log/Log.h>

PWM::PWM(){

}

PWM::PWM(uint8_t PWM, uint16_t PWM_GEN_, uint32_t freq)
{
    Log::logDoing("Initialize PWM %d", PWM);

    // TODO Auto-generated constructor stub
    uint32_t SYSCTL_PERIPH_PWM;
    PWM_GEN = PWM_GEN_;
    ulPeriod = SysCtlClockGet()/freq;

    switch(PWM){
    case PWM0:
        SYSCTL_PERIPH_PWM = SYSCTL_PERIPH_PWM0;
        PWM_BASE = PWM0_BASE;
        break;
    case PWM1:
        SYSCTL_PERIPH_PWM = SYSCTL_PERIPH_PWM1;
        PWM_BASE = PWM1_BASE;
        break;
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_PWM)));

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    PWMGenConfigure(PWM_BASE, PWM_GEN, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN, ulPeriod);
    PWMGenEnable(PWM_BASE, PWM_GEN);

    Log::logDone("Initialize PWM %d", PWM);
}

PWM::~PWM()
{
    // TODO Auto-generated destructor stub
}

void PWM::setOutMode(uint8_t PWM_OUT_BIT, uint8_t PORT, uint8_t GPIO_PIN_, uint32_t GPIO_P_MPWM, uint8_t duty){

    uint32_t SYSCTL_PERIPH_GPIO;
    uint32_t GPIO_PORT_BASE;

    switch(PORT){
    case PORTA:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOA;
        GPIO_PORT_BASE = GPIO_PORTA_BASE;
        break;
    case PORTB:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOB;
        GPIO_PORT_BASE = GPIO_PORTB_BASE;
        break;
    case PORTC:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOC;
        GPIO_PORT_BASE = GPIO_PORTC_BASE;
        break;
    case PORTD:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOD;
        GPIO_PORT_BASE = GPIO_PORTD_BASE;
        break;
    case PORTE:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOE;
        GPIO_PORT_BASE = GPIO_PORTE_BASE;
        break;
    case PORTF:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE = GPIO_PORTF_BASE;
        break;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO)));

    GPIOPinTypePWM(GPIO_PORT_BASE, GPIO_PIN_);
    GPIOPinConfigure(GPIO_P_MPWM);

    uint32_t PWM_OUT_;
    switch(PWM_OUT_BIT){
    case PWM_OUT_0_BIT:
        PWM_OUT_ = PWM_OUT_0;
        break;
    case PWM_OUT_1_BIT:
        PWM_OUT_ = PWM_OUT_1;
        break;
    case PWM_OUT_2_BIT:
        PWM_OUT_ = PWM_OUT_2;
        break;
    case PWM_OUT_3_BIT:
        PWM_OUT_ = PWM_OUT_3;
        break;
    case PWM_OUT_4_BIT:
        PWM_OUT_ = PWM_OUT_4;
        break;
    case PWM_OUT_5_BIT:
        PWM_OUT_ = PWM_OUT_5;
        break;
    case PWM_OUT_6_BIT:
        PWM_OUT_ = PWM_OUT_6;
        break;
    case PWM_OUT_7_BIT:
        PWM_OUT_ = PWM_OUT_7;
        break;
    }

    PWMPulseWidthSet(PWM_BASE, PWM_OUT_, ulPeriod * duty / 100);
    PWMOutputState(PWM_BASE, PWM_OUT_BIT, true);
}

void PWM::setDuty(uint32_t PWM_OUT_, float duty){
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_, ulPeriod * duty / 100);
}
