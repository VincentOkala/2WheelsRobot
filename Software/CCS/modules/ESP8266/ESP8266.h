/*
 * ESP8266.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef MODULES_ESP8266_ESP8266_H_
#define MODULES_ESP8266_ESP8266_H_

#include <peripheral/UART/UART.h>

typedef void (*UARTOnReceive)(char);

class ESP8266
{
public:
    ESP8266();
    virtual ~ESP8266();

    void reset();
    void connect();
    void startServer();
    void setOnReceiveFcn(UARTOnReceive UARTOnReceive_);

private:
    static UART uart;
    static UARTOnReceive uartOnReceive;
    static void UARTIntHandler();

};

#endif /* MODULES_ESP8266_ESP8266_H_ */
