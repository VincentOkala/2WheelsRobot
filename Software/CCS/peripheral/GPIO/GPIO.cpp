/*
 * GPIO.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: Light
 */

#include <peripheral/GPIO/GPIO.h>
#include <slib/log/Log.h>

GPIO::GPIO(){

}

GPIO::GPIO(uint8_t port)
{
    // TODO Auto-generated constructor stub
    Log::logDoing("Initialize GPIO port %d", port);

    uint32_t SYSCTL_PERIPH_GPIO;
    switch(port){
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

    Log::logDone("Initialize GPIO port %d", port);
}

GPIO::~GPIO()
{
    // TODO Auto-generated destructor stub
}

void GPIO::mode(uint8_t GPIO_PIN_, uint8_t MODE_){
    switch(MODE_){
    case MODE_OUTPUT:
        GPIOPinTypeGPIOOutput(GPIO_PORT_BASE, GPIO_PIN_);
        break;
    case MODE_INPUT:
        GPIOPinTypeGPIOInput(GPIO_PORT_BASE, GPIO_PIN_);
        break;
    }
}

void GPIO::write(uint8_t GPIO_PIN_, uint8_t VALUE_){
    switch(VALUE_){
    case VALUE_ON:
        GPIOPinWrite(GPIO_PORT_BASE, GPIO_PIN_, GPIO_PIN_);
        break;
    case VALUE_OFF:
        GPIOPinWrite(GPIO_PORT_BASE, GPIO_PIN_, 0);
        break;
    }
}
