/*
 * ESP8266.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef MODULES_ESP8266_ESP8266_H_
#define MODULES_ESP8266_ESP8266_H_

#include <peripheral/UART/UART.h>
#include "../../slib/Console/Console.h"
#include "../../slib/Params/Params.h"

typedef enum{
    NEXT_STT,
    READY,
    RESETING,
    WIFI_CONNECTING,
    READ_FULL_PARAM,
    READ_PARAM
}ESP8266_STT;

class ESP8266
{
public:
    ESP8266(Params* params);
    virtual ~ESP8266();
    static void UARTIntHandler();
    static void paramParse();
    static void reset();
    static void connect();
    static void readFullParamList();
    static void startServer();

    static UART uart;
private:

    static bool getKeyValue(char* key, char* value);

    static Params* param;

    static char buf[100];
    static uint8_t bufIndex;

    static ESP8266_STT esp8266Status;
};

#endif /* MODULES_ESP8266_ESP8266_H_ */
