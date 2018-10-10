/*
 * ESP8266.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef MODULES_ESP8266_ESP8266_H_
#define MODULES_ESP8266_ESP8266_H_

#include <peripheral/UART/UART.h>

typedef enum{
    ESP8266_BEGIN,
    ESP8266_READY_BEFORE_RESET, // >>>
    ESP8266_READY_AFTER_RESET, // >>>
    ESP8266_SERVER_RUNNING, // OK
}ESP8266_STT;

typedef void (*UARTOnReceive)(char);

class ESP8266
{
public:
    ESP8266();
    virtual ~ESP8266();
    static void reset();
    static void connect();
    static void startServer();
    static void setOnReceiveFcn(UARTOnReceive UARTOnReceive_);
private:
    static ESP8266_STT esp8266Status;
    static UARTOnReceive uartOnReceive;
    static void UARTIntHandler();
    static UART uart;
};

#endif /* MODULES_ESP8266_ESP8266_H_ */
