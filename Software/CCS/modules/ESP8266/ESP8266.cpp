/*
 * ESP8266.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#include <modules/ESP8266/ESP8266.h>
#include <slib/Log/Log.h>

#include <slib/System/System.h>
#include <define.h>

#include <string.h>
#include <stdlib.h>

UART ESP8266::uart;
UARTOnReceive ESP8266::uartOnReceive = 0;

ESP8266::ESP8266()
{
    uart = UART(ESP8266_UART, ESP8266_UART_BAUD);

    IntEnable(uart.INT_UART);
    UARTIntEnable(uart.UART_BASE, UART_INT_RX);

    UARTIntRegister(uart.UART_BASE, ESP8266::UARTIntHandler);
    UARTFIFODisable(uart.UART_BASE);

    reset();
    connect();
    startServer();
}

ESP8266::~ESP8266(){}

void ESP8266::reset(){}

void ESP8266::connect(){}

void ESP8266::startServer(){}

void ESP8266::setOnReceiveFcn(UARTOnReceive UARTOnReceive_){
    uartOnReceive = UARTOnReceive_;
}

void ESP8266::UARTIntHandler()
{
    uint32_t ui32Status = UARTIntStatus(uart.UART_BASE, true);
    UARTIntClear(uart.UART_BASE, ui32Status);
    uint8_t chr;
    while(UARTCharsAvail(uart.UART_BASE))
    {
        chr = UARTCharGet(uart.UART_BASE);
        if(uartOnReceive != 0){
            uartOnReceive(chr);
        }
    }
}
