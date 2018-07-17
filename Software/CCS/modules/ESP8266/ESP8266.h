/*
 * ESP8266.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef MODULES_ESP8266_ESP8266_H_
#define MODULES_ESP8266_ESP8266_H_

#include <peripheral/UART/UART.h>
#include <modules/ESP8266/PARAMETER/PARAMETER.h>
#include <slib/CONSOLE/CONSOLE.h>

typedef enum{
    READY,
    RESETING,
    WIFI_CONNECTING,
    READ_PARAM,
}ESP8266_STT;

class ESP8266
{
public:
    ESP8266();
    virtual ~ESP8266();
    static void UARTIntHandler();
    static void UartRxISR();
    void reset();
    void connect();
    void readFullParamList();
    static bool getKey(char *key);
    static bool getValue(char *value);

    static UART uart;
private:

    static PARAMETER param;

    static char buf[100];
    static uint8_t bufIndex;
    static uint8_t getFunctionIndex;
    static bool end;

    static ESP8266_STT esp8266Status;
};

#endif /* MODULES_ESP8266_ESP8266_H_ */
