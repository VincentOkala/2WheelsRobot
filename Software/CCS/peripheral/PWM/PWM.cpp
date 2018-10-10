/*
 * PWM.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: light
 */

#include <peripheral/PWM/PWM.h>

PWM::PWM(){}
PWM::~PWM(){}

/**
 * @brief Construct a new PWM::PWM object
 * 
 * @param PWM_ PWM_0 v PWM_1
 * @param PWM_GEN_ GEN_0 --> GEN_3
 * @param freq 1221 --> SysCtlClockGet() Hz
 */
PWM::PWM(PWM_ PWM_, PWM_GEN_ PWM_GEN_, uint32_t freq)
{
    // TODO Auto-generated constructor stub
    uint32_t SYSCTL_PERIPH_PWM;

    switch(PWM_){
    case PWM_0:
        SYSCTL_PERIPH_PWM = SYSCTL_PERIPH_PWM0;
        PWM_BASE = PWM0_BASE;
        break;
    case PWM_1:
        SYSCTL_PERIPH_PWM = SYSCTL_PERIPH_PWM1;
        PWM_BASE = PWM1_BASE;
        break;
    }

    switch(PWM_GEN_){
    case GEN_0:
        PWM_GEN = PWM_GEN_0;
        PWM_OUT_A = PWM_OUT_0;
        PWM_OUT_B = PWM_OUT_1;
        break;
    case GEN_1:
        PWM_GEN = PWM_GEN_1;
        PWM_OUT_A = PWM_OUT_2;
        PWM_OUT_B = PWM_OUT_3;
        break;
    case GEN_2:
        PWM_GEN = PWM_GEN_2;
        PWM_OUT_A = PWM_OUT_4;
        PWM_OUT_B = PWM_OUT_5;
        break;
    case GEN_3:
        PWM_GEN = PWM_GEN_3;
        PWM_OUT_A = PWM_OUT_6;
        PWM_OUT_B = PWM_OUT_7;
        break;
    }

    ulPeriod = SysCtlClockGet()/freq;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_PWM)));

    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    PWMGenConfigure(PWM_BASE, PWM_GEN, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM_BASE, PWM_GEN, ulPeriod);
    PWMGenEnable(PWM_BASE, PWM_GEN);
}

/**
 * @brief Set duty for PWM 0 of a PWM generator
 * 
 * @param duty 0 --> 100 %
 */
void PWM::setDutyA(float duty){
    duty = duty > 100 ? 100 : duty;
    duty = duty < 0 ? 0 : duty;
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_A, ulPeriod * duty / 100);
}

/**
 * @brief Set duty for PWM 1 of a PWM generator
 * 
 * @param duty 0 --> 100 %
 */
void PWM::setDutyB(float duty){
    duty = duty > 100 ? 100 : duty;
    duty = duty < 0 ? 0 : duty;
    PWMPulseWidthSet(PWM_BASE, PWM_OUT_B, ulPeriod * duty / 100);
}

/**
 * @brief Choose a pin as pwm output pin
 * 
 * @param GPIO_PORT_ GPIO_PORT_A --> GPIO_PORT_F
 * @param GPIO_PIN_ GPIO_PIN_0 --> GPIO_PIN_7
 * @param GPIO_P_MPWM GPIO_P<PortPin>_M<0 v 1>PWM<0 --> 7>
 */
void PWM::configOutPin(GPIO_PORT_ GPIO_PORT_, uint8_t GPIO_PIN_, uint32_t GPIO_P_MPWM){

    uint32_t SYSCTL_PERIPH_GPIO;
    uint32_t GPIO_PORT_BASE;

    switch(GPIO_PORT_){
    case GPIO_PORT_A:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOA;
        GPIO_PORT_BASE = GPIO_PORTA_BASE;
        break;
    case GPIO_PORT_B:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOB;
        GPIO_PORT_BASE = GPIO_PORTB_BASE;
        break;
    case GPIO_PORT_C:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOC;
        GPIO_PORT_BASE = GPIO_PORTC_BASE;
        break;
    case GPIO_PORT_D:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOD;
        GPIO_PORT_BASE = GPIO_PORTD_BASE;
        break;
    case GPIO_PORT_E:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOE;
        GPIO_PORT_BASE = GPIO_PORTE_BASE;
        break;
    case GPIO_PORT_F:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOF;
        GPIO_PORT_BASE = GPIO_PORTF_BASE;
        break;
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO)));

    GPIOPinTypePWM(GPIO_PORT_BASE, GPIO_PIN_);
    GPIOPinConfigure(GPIO_P_MPWM);
}

