/*
 * UART.cpp
 *
 *  Created on: May 9, 2018
 *      Author: light
 */

#include <peripheral/UART/UART.h>

UART::UART()
{
    // TODO Auto-generated constructor stub

}

UART::UART(uint8_t ID){
    switch(ID){
    case UART0:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOA;
        SYSCTL_PERIPH_UART = SYSCTL_PERIPH_UART0;
        GPIO_P_URX = GPIO_PA0_U0RX;
        GPIO_P_UTX = GPIO_PA1_U0TX;
        GPIO_PORT_BASE  = GPIO_PORTA_BASE;
        GPIO_PIN_RX     = GPIO_PIN_0;
        GPIO_PIN_TX     = GPIO_PIN_1;
        UART_BASE       = UART0_BASE;
        break;
    case UART1:
        break;
    case UART2:
        break;
    case UART3:
        break;
    case UART4:
        break;
    case UART5:
        break;
    case UART6:
        break;
    case UART7:
        break;
    }
}

UART::~UART()
{
    // TODO Auto-generated destructor stub
}

bool UART::Init(uint32_t BAUDRATE){

    // Enable the GPIO peripheral for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO)));

    // Enable the UART peripheral for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UART)));

    GPIOPinConfigure(GPIO_P_URX);
    GPIOPinConfigure(GPIO_P_UTX);

    GPIOPinTypeUART(GPIO_PORT_BASE, GPIO_PIN_TX | GPIO_PIN_RX);

    UARTClockSourceSet(UART_BASE, UART_CLOCK_PIOSC);

    // Configure the UART for BAUDRATE, n, 8, 1
    UARTConfigSetExpClk(UART_BASE, SysCtlClockGet(), BAUDRATE,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));

    // Enable the UART operation.
    UARTEnable(UART_BASE);
    return true;
}

bool UART::send(const char *str, uint8_t length){
    uint8_t index;
    for(index = 0; index < length; index++){
        UARTCharPut(UART_BASE, str[index]);
    }
    return true;
}

bool UART::reicv(uint8_t *str, uint8_t length){
    uint8_t index;
    for(index = 0; index < length; index++){
        str[index] = UARTCharGet(UART_BASE);
    }
    return true;
}
