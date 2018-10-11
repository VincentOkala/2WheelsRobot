/*
 * CC1101.h
 *
 *  Created on: Oct 11, 2018
 *      Author: 16138
 */

#ifndef MODULES_CC1101_CC1101_H_
#define MODULES_CC1101_CC1101_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <peripheral/UART/UART.h>
#include <define.h>

typedef void (*UARTOnReceive)(char);

typedef enum{
    CC1101_IDLE,
    CC1101_BUSY
}CC1101_STT;

typedef struct{
    uint8_t* pkgPtr;
    uint16_t len;
    uint16_t index;
}PKG;

class CC1101
{
public:
    CC1101();
    virtual ~CC1101();

    void init();
    bool send(uint8_t* arr, uint16_t len);
    void setCallBack(UARTOnReceive _uartOnReceive);
private:
    static UART uart;
    static UARTOnReceive uartOnReceive;
    static CC1101_STT cc1101_stt;
    static PKG pkg;

    static void UARTIntHandler();
};

#endif /* MODULES_CC1101_CC1101_H_ */
