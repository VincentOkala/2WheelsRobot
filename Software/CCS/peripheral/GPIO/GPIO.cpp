/*
 * GPIO.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: Light
 */

#include <peripheral/GPIO/GPIO.h>
#include <slib/Log/Log.h>

GPIO::GPIO(){}
GPIO::~GPIO(){}

/**
 * @brief Construct a new GPIO::GPIO object
 * 
 * @param GPIO_PORT_ GPIO_PORT_A --> GPIO_PORT_F
 */
GPIO::GPIO(GPIO_PORT_ GPIO_PORT_)
{
    uint32_t SYSCTL_PERIPH_GPIO;
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

}

/**
* @brief choose mode for a pin
* 
* @param GPIO_PIN_ GPIO_PIN_0 --> GPIO_PIN_7
* @param MODE_ GPIO_MODE_OUTPUT v GPIO_MODE_INPUT
*/
void GPIO::mode(uint8_t GPIO_PIN_, GPIO_MODE_ GPIO_MODE_){
    switch(GPIO_MODE_){
    case GPIO_MODE_OUTPUT:
        GPIOPinTypeGPIOOutput(GPIO_PORT_BASE, GPIO_PIN_);
        break;
    case GPIO_MODE_INPUT:
        GPIOPinTypeGPIOInput(GPIO_PORT_BASE, GPIO_PIN_);
        break;
    }
}

/**
 * @brief Turn a pin on or off
 * 
 * @param GPIO_PIN_ GPIO_PIN_0 --> GPIO_PIN_7
 * @param VALUE_ VALUE_ON v VALUE_OFF
 */
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

/**
 * @brief read value of 
 * 
 * @param GPIO_PIN_ GPIO_PIN_0 --> GPIO_PIN_7 or any combination of them, for example (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2)
 * @return uint8_t Returns a bit-packed byte providing the state of the specified pin, where bit 0 of the byte
                   represents GPIO port pin 0, bit 1 represents GPIO port pin 1, and so on. Any bit that is not
                   specified by ui8Pins is returned as a 0. Bits 31:8 should be ignored.
 */
uint8_t GPIO::read(uint8_t GPIO_PIN_){
    return GPIOPinRead(GPIO_PORT_BASE, GPIO_PIN_);
}
