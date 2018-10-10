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

void donothing(char dummychr){}

UART ESP8266::uart;
ESP8266_STT ESP8266::esp8266Status;
UARTOnReceive ESP8266::uartOnReceive = &donothing;

ESP8266::ESP8266()
{
    Log::logDoing("Initialize ESP8266");

    uart = UART(ESP8266_UART, ESP8266_UART_BAUD);

    IntEnable(uart.INT_UART);
    UARTIntEnable(uart.UART_BASE, UART_INT_RX);
    UARTIntRegister(uart.UART_BASE, ESP8266::UARTIntHandler);
    UARTFIFODisable(uart.UART_BASE);

    esp8266Status = ESP8266_BEGIN;

    reset();
    connect();
    startServer();

    Log::logDone("Initialize ESP8266: DONE");
}

ESP8266::~ESP8266(){}

void ESP8266::reset(){}

void ESP8266::connect(){}

void ESP8266::startServer(){}

void ESP8266::setOnReceiveFcn(UARTOnReceive UARTOnReceive_){
    uartOnReceive = UARTOnReceive_;
}

void ESP8266::UARTIntHandler(void)
{
    uint32_t ui32Status = UARTIntStatus(uart.UART_BASE, true);
    UARTIntClear(uart.UART_BASE, ui32Status);
    uint8_t chr;
    while(UARTCharsAvail(uart.UART_BASE))
    {
        chr = UARTCharGet(uart.UART_BASE);
        uartOnReceive(chr);
    }
}
