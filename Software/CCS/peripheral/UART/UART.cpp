/*
 * UART.cpp
 *
 *  Created on: May 9, 2018
 *      Author: light
 */

#include <peripheral/UART/UART.h>

UART::UART(){}
UART::~UART(){}

/**
 * @brief Construct a new UART::UART object
 * 
 * @param UART_ UART_0 --> UART_7
 * @param BAUDRATE 115200 v 9600 v ...
 */
UART::UART(UART_ UART_, uint32_t BAUDRATE){
    uint32_t SYSCTL_PERIPH_GPIO;
    uint32_t SYSCTL_PERIPH_UART;

    uint32_t GPIO_P_URX;
    uint32_t GPIO_P_UTX;

    uint32_t GPIO_PORT_BASE;
    uint32_t GPIO_PIN_TX;
    uint32_t GPIO_PIN_RX;

    switch(UART_){
    case UART_0:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOA;
        SYSCTL_PERIPH_UART = SYSCTL_PERIPH_UART0;
        GPIO_P_URX = GPIO_PA0_U0RX;
        GPIO_P_UTX = GPIO_PA1_U0TX;
        GPIO_PORT_BASE  = GPIO_PORTA_BASE;
        GPIO_PIN_RX     = GPIO_PIN_0;
        GPIO_PIN_TX     = GPIO_PIN_1;
        UART_BASE       = UART0_BASE;
        INT_UART        = INT_UART0;
        break;
    case UART_1:
        SYSCTL_PERIPH_GPIO = SYSCTL_PERIPH_GPIOB;
        SYSCTL_PERIPH_UART = SYSCTL_PERIPH_UART1;
        GPIO_P_URX = GPIO_PB0_U1RX;
        GPIO_P_UTX = GPIO_PB1_U1TX;
        GPIO_PORT_BASE  = GPIO_PORTB_BASE;
        GPIO_PIN_RX     = GPIO_PIN_0;
        GPIO_PIN_TX     = GPIO_PIN_1;
        UART_BASE       = UART1_BASE;
        INT_UART        = INT_UART1;
        break;
    case UART_2:
        break;
    case UART_3:
        break;
    case UART_4:
        break;
    case UART_5:
        break;
    case UART_6:
        break;
    case UART_7:
        break;
    }

    // Enable the GPIO peripheral for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIO);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIO)));

    // Enable the UART peripheral for use.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UART)));

    GPIOPinConfigure(GPIO_P_URX);
    GPIOPinConfigure(GPIO_P_UTX);

    GPIOPinTypeUART(GPIO_PORT_BASE, GPIO_PIN_TX | GPIO_PIN_RX);

    UARTClockSourceSet(UART_BASE, TIMER_CLOCK_SYSTEM);

    // Configure the UART for BAUDRATE, n, 8, 1
    UARTConfigSetExpClk(UART_BASE, SysCtlClockGet(), BAUDRATE,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));

    // Enable the UART operation.
    UARTEnable(UART_BASE);
}

/**
 * @brief Send an array width length via serial port
 * 
 * @param str Pointer to array
 * @param length Length of array
 */
void UART::send(const char *str, uint8_t length){
    uint8_t index;
    for(index = 0; index < length; index++){
        UARTCharPut(UART_BASE, str[index]);
    }
}

/**
 * @brief Send a string via serial port
 * 
 * @param str Pointer to string
 */
void UART::send(const char *str){
    uint8_t length = 0;
    while(str[length] != 0) length++;
    uint8_t index;
    for(index = 0; index < length; index++){
        UARTCharPut(UART_BASE, str[index]);
    }
}

/**
 * @brief Receive an array from serial port. This is a bloking function
 * 
 * @param str Pointer to receiver array
 * @param length Length of package 
 */
void UART::reicv(uint8_t *str, uint8_t length){
    uint8_t index;
    for(index = 0; index < length; index++){
        str[index] = UARTCharGet(UART_BASE);
    }
}

/**
 * @brief Receive an array from serial port until read the delimiter
 * 
 * @param str Pointer to receiver array
 * @param delimiter End token
 * @return uint8_t Length of the package
 */
uint8_t UART::reicv(uint8_t *str, char delimiter){
    uint8_t index = 0;
    do{
        str[index] = UARTCharGet(UART_BASE);
        index++;
    }
    while( str[index-1] != delimiter);
    return index;
}
