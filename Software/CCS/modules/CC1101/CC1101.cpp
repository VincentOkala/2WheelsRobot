/*
 * CC1101.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: 16138
 */

#include <modules/CC1101/CC1101.h>

CC1101::CC1101(){}
CC1101::~CC1101(){}

UART CC1101::uart;
UARTOnReceive CC1101::uartOnReceive = 0;
CC1101_STT CC1101::cc1101_stt;
PKG CC1101::pkg;

void CC1101::init(){
    uart = UART(CC1101_UART, CC1101_UART_BAUD);

    IntEnable(uart.INT_UART);
    UARTIntEnable(uart.UART_BASE, UART_INT_RX);

    UARTIntRegister(uart.UART_BASE, UARTIntHandler);
    UARTFIFODisable(uart.UART_BASE);

    cc1101_stt = CC1101_IDLE;
}

bool CC1101::send(uint8_t* arr, uint16_t len){
    if(cc1101_stt == CC1101_BUSY) return false;
    else{
        cc1101_stt = CC1101_BUSY;
        pkg.pkgPtr = arr;
        pkg.len = len;
        pkg.index = 0;
        UARTIntEnable(uart.UART_BASE, UART_INT_TX);
        return true;
    }
}

void CC1101::setCallBack(UARTOnReceive _uartOnReceive){
    uartOnReceive = _uartOnReceive;
}

void CC1101::UARTIntHandler(){
    uint32_t ui32Status = UARTIntStatus(uart.UART_BASE, true);
    UARTIntClear(uart.UART_BASE, ui32Status);
    uint8_t chr;
    if(ui32Status & UART_INT_RX){
        while(UARTCharsAvail(uart.UART_BASE))
        {
            chr = UARTCharGet(uart.UART_BASE);
            if(uartOnReceive != 0){
                uartOnReceive(chr);
            }
        }
    }
    if(ui32Status & UART_INT_TX){
        UARTCharPut(uart.UART_BASE, pkg.pkgPtr[pkg.index]);
        pkg.index++;
        if(pkg.index == pkg.len){
            cc1101_stt = CC1101_IDLE;
            UARTIntDisable(uart.UART_BASE, UART_INT_TX);
        }
    }
}
