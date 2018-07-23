/*
 * ESP8266.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#include <modules/ESP8266/ESP8266.h>
#include <slib/Log/Log.h>

#include <slib/System/System.h>

#include <string.h>
#include <stdlib.h>

#define RX_BUFF_SIZE 100
#define MAX_TRY_TIME 10

UART ESP8266::uart;
Params* ESP8266::param;

uint8_t ESP8266::bufIndex = 0;
char ESP8266::buf[RX_BUFF_SIZE];
ESP8266_STT ESP8266::esp8266Status;

ESP8266::ESP8266(Params* params)
{
    // TODO Auto-generated constructor stub

    Log::logDoing("Initialize ESP8266");

    param = params;
    uart = UART(UART_1, 115200);


    IntEnable(uart.INT_UART);
    UARTIntEnable(uart.UART_BASE, UART_INT_RX);
    UARTIntRegister(uart.UART_BASE, ESP8266::UARTIntHandler);
    UARTFIFODisable(uart.UART_BASE);
    IntMasterEnable();  // Enable master interrupt

    esp8266Status = NEXT_STT;

    reset();
    connect();
    readFullParamList();
    startServer();

    esp8266Status = READ_PARAM;

    Log::logDone("Initialize ESP8266: DONE");
}

ESP8266::~ESP8266()
{
    // TODO Auto-generated destructor stub
}

void ESP8266::reset(){
    UARTCharPut(uart.UART_BASE, 0x03);
    System::delayMs(500);

    esp8266Status = READY;
    Log::logDoing("Checking if ESP8266 is ready");
    UARTCharPut(uart.UART_BASE, '\r');
    while(esp8266Status == READY){
        System::delayMs(500);
        UARTCharPut(uart.UART_BASE, '\r');
    }
    Log::logDone("ESP8266 is ready");

    esp8266Status = RESETING;
    Log::logDoing("Reseting ESP8266");
    const char* cmd1 = "import machine\r\n";
    uart.send(cmd1,strlen(cmd1));
    const char*cmd2 = "machine.reset()\r\n";
    uart.send(cmd2,strlen(cmd2));
    Log::logStr("Waiting...");
    while(esp8266Status == RESETING){
        Log::logStr(".");
        System::delayMs(100);
    }
    Log::logStr("\r\n");
    Log::logDone("ESP8266 has been reseted");
}

void ESP8266::connect(){
    Log::logDoing("Wifi connecting");
    const char* cmd3 = "import wifi\r\n";
    uart.send(cmd3,strlen(cmd3));
    System::delayMs(500);

    esp8266Status = WIFI_CONNECTING;
    const char* cmd4 = "wifi.connect(";
    uart.send(cmd4,strlen(cmd4));
    const char* cmd5 = "\'DHBK_PUBLIC\', \'copass*0?\')\r\n";
    uart.send(cmd5,strlen(cmd5));
    Log::logStr("Waiting...");
    while(esp8266Status == WIFI_CONNECTING){
        Log::logStr(".");
        System::delayMs(100);
    }
    Log::logStr("\r\n");
    Log::logDone("Wifi connecting");
}

void ESP8266::readFullParamList(){
    Log::logDoing("Updating Parameters");

    const char* cmd1 = "f = open('param.json','r') \r\n";
    uart.send(cmd1, strlen(cmd1));
    System::delayMs(500);

    esp8266Status = READ_FULL_PARAM;
    bufIndex = 0;

    const char* cmd2 = "f.read()\r";
    uart.send(cmd2, strlen(cmd2));

    Log::logStr("Waiting...");
    while(esp8266Status == READ_FULL_PARAM){
        Log::logStr(".");
        System::delayMs(100);
    }
    Log::logStr("\r\n");
    Log::logDone("Parameters Updated");
}

void ESP8266::startServer(){
    Log::logDoing("Starting Server");
    const char* cmd3 = "import server.py\r\n";
    uart.send(cmd3, strlen(cmd3));
    bufIndex = 0;
    Log::logDone("Server started");
}


uint8_t count = 0;
void ESP8266::UARTIntHandler(void)
{
    uint32_t ui32Status = UARTIntStatus(uart.UART_BASE, true);
    UARTIntClear(uart.UART_BASE, ui32Status);
    char chr;
    while(UARTCharsAvail(uart.UART_BASE))
    {
        chr = UARTCharGet(uart.UART_BASE);
        if(esp8266Status == READY){
            if(chr == '>') count++;
            else count = 0;
            if(count == 3){
                count = 0;
                esp8266Status = NEXT_STT;
            }
        }
        else if(esp8266Status == RESETING){
            if(chr == '>') count++;
            if(count == 9){
                count = 0;
                esp8266Status = NEXT_STT;
            }
        }
        else if(esp8266Status == WIFI_CONNECTING){
            if(chr == '>') count++;
            else count = 0;
            if(count == 3){
                count = 0;
                esp8266Status = NEXT_STT;
            }
        }
        else if (esp8266Status == READ_FULL_PARAM){
            if(chr == '\n'){
                buf[bufIndex] = 0;  // make buffer as a string
                if(buf[0]=='\'' && buf[1] == '{'){
                    paramParse();
                    esp8266Status = NEXT_STT;
                }
                bufIndex = 0;
            }
            else{
                buf[bufIndex] = chr;
                if(bufIndex < RX_BUFF_SIZE) bufIndex++;
            }

        }
        else if (esp8266Status == READ_PARAM){
            if(chr == '\n'){
                buf[bufIndex] = 0; // make buffer as a string
                if(buf[0]=='\'' && buf[1] == '{'){
                    paramParse();
                }
                bufIndex = 0;
            }
            else{
                buf[bufIndex] = chr;
                if(bufIndex < RX_BUFF_SIZE) bufIndex++;
            }

        }
    }
}

uint8_t discardIndex = 0;
bool ESP8266::getKeyValue(char* key, char* value){
    uint8_t tryTime = 1;
    while(buf[discardIndex] != '\"'){
        discardIndex++;
        tryTime++;
        if((tryTime == MAX_TRY_TIME) || (discardIndex == RX_BUFF_SIZE)){
            discardIndex = 0;
            return false;
        }
    }
    discardIndex++;

    uint8_t keyIndex = 0;
    uint8_t valueIndex = 0;

    while(buf[discardIndex] != '\"'){
        key[keyIndex] = buf[discardIndex];
        discardIndex++;
        keyIndex++;
    }
    keyIndex++;
    key[keyIndex] = 0;

    discardIndex += 3;
    while(buf[discardIndex] != ',' && buf[discardIndex] != '}'){
        value[valueIndex] = buf[discardIndex];
        discardIndex++;
        valueIndex++;
    }

    valueIndex++;
    value[valueIndex] = 0;

    return true;
}

bool compareString(const char* str1, const char * str2){
    uint8_t index = 0;
    while(str1[index] != 0){
        if (str1[index] != str2[index]) return false;
        index++;
    }
    if (str2[index] == 0) return true;
    else return false;
}

void ESP8266::paramParse(){
    char key[10] = "", value[10] = "";
    while(getKeyValue(key, value)){
        if(compareString(key, "Kp")) param->Kp = atof(value);
        if(compareString(key, "Ki")) param->Ki = atof(value);
        if(compareString(key, "Kd")) param->Kd = atof(value);
    }
}
