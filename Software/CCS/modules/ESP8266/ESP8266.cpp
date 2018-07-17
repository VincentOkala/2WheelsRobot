/*
 * ESP8266.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#include <modules/ESP8266/ESP8266.h>

#include <slib/system/System.h>
#include <slib/Log/Log.h>

#include <string.h>
#include <stdlib.h>

UART ESP8266::uart;
PARAMETER ESP8266::param = PARAMETER();

uint8_t ESP8266::bufIndex = 0;
uint8_t ESP8266::getFunctionIndex = 0;
bool ESP8266::end = false;
char ESP8266::buf[100];
ESP8266_STT ESP8266::esp8266Status;

ESP8266::ESP8266()
{
    // TODO Auto-generated constructor stub

    Log::logDoing("Initialize ESP8266");

    uart = UART(UART_1, 115200);


    IntEnable(uart.INT_UART);
    UARTIntEnable(uart.UART_BASE, UART_INT_RX);
    UARTIntRegister(uart.UART_BASE, ESP8266::UARTIntHandler);
    UARTFIFODisable(uart.UART_BASE);
    IntMasterEnable();  // Enable master interrupt

    reset();
    System::delayMs(1000);
    connect();
//    readFullParamList();
//    const char* cmd = "import server.py\r\n";
//    uart.send(cmd, strlen(cmd));

    Log::logDone("Initialize ESP8266: DONE");
}

ESP8266::~ESP8266()
{
    // TODO Auto-generated destructor stub
}

void ESP8266::reset(){
    esp8266Status = READY;

    Log::logDoing("Checking if ESP8266 is ready");
    UARTCharPut(uart.UART_BASE, '\r');
    UARTCharPut(uart.UART_BASE, '\n');
    while(esp8266Status == READY){
        System::delayMs(1000);
        UARTCharPut(uart.UART_BASE, '\r');
        UARTCharPut(uart.UART_BASE, '\n');
    }
    Log::logDone("Checking if ESP8266 is ready");

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
    Log::logDone("Reseting ESP8266 : DONE");
}

void ESP8266::connect(){
    Log::logDoing("Wifi connecting");
    const char* cmd3 = "import wifi\r\n";
    uart.send(cmd3,strlen(cmd3));
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
    Log::logInfo("Updating Parameters...");

    const char* cmd1 = "f = open('param.json','r') \r\n";
    uart.send(cmd1, strlen(cmd1));

    const char* cmd2 = "f.read()\r\n";
    uart.send(cmd2, strlen(cmd2));

    const char* cmd3 = "import server.py\r\n";
    uart.send(cmd3, strlen(cmd3));
    bufIndex = 0;

    Log::logInfo("Updating Parameters: DONE");
}

uint8_t count = 0;
uint8_t flag = 0;
void ESP8266::UARTIntHandler(void)
{
    uint32_t ui32Status = UARTIntStatus(uart.UART_BASE, true);
    UARTIntClear(uart.UART_BASE, ui32Status);
    char chr;
    while(UARTCharsAvail(uart.UART_BASE))
    {
        chr = UARTCharGet(uart.UART_BASE);
        if(esp8266Status == READY){
            if(chr == '>')
                count++;
            if(count == 3){
                count = 0;
                esp8266Status = RESETING;
            }
        }
        else if(esp8266Status == RESETING){
            if(chr == '>') count++;
            else count = 0;
            if(count == 3){
                count = 0;
                esp8266Status = WIFI_CONNECTING;
            }
        }
        else if(esp8266Status == WIFI_CONNECTING){
            if(chr == '>') count++;
            if(count == 100){
                count = 0;
                esp8266Status = READ_PARAM;
            }
        }
        else if (esp8266Status == READ_PARAM){
            if(chr == '\n'){
                buf[bufIndex] = 0;
                if(buf[0]=='\'' && buf[1] == '{'){
                    UartRxISR();
                }
                bufIndex = 0;
            }
            else{
                buf[bufIndex] = chr;
                if(bufIndex < 100) bufIndex++;
            }

        }
    }
}

bool ESP8266::getKey(char *key){
    if(end == true) return false;
    uint8_t keyIndex = 0;
    while(buf[getFunctionIndex] == '\'' || buf[getFunctionIndex] == '{' || buf[getFunctionIndex] == '}' || buf[getFunctionIndex] == '\"' ||  buf[getFunctionIndex] == ' ' || buf[getFunctionIndex] == ',' || buf[getFunctionIndex] == ':') getFunctionIndex++;
    while(buf[getFunctionIndex] != '\'' && buf[getFunctionIndex] != '{' && buf[getFunctionIndex] != '}' && buf[getFunctionIndex] != '\"' &&  buf[getFunctionIndex] != ' ' && buf[getFunctionIndex] != ',' && buf[getFunctionIndex] != ':') {
        key[keyIndex] = buf[getFunctionIndex];
        keyIndex++;
        getFunctionIndex++;
    }
    keyIndex++;
    key[keyIndex] = 0;
    return true;
}
bool ESP8266::getValue(char *value){
    uint8_t valueIndex = 0;
    while(buf[getFunctionIndex] == '\'' || buf[getFunctionIndex] == '{' || buf[getFunctionIndex] == '}' || buf[getFunctionIndex] == '\"' ||  buf[getFunctionIndex] == ' ' || buf[getFunctionIndex] == ',' || buf[getFunctionIndex] == ':') getFunctionIndex++;
    while(buf[getFunctionIndex] != '\'' && buf[getFunctionIndex] != '{' && buf[getFunctionIndex] != '}' && buf[getFunctionIndex] != '\"' &&  buf[getFunctionIndex] != ' ' && buf[getFunctionIndex] != ',' && buf[getFunctionIndex] != ':') {
        value[valueIndex] = buf[getFunctionIndex];
        valueIndex++;
        getFunctionIndex++;
    }
    if (buf[getFunctionIndex] == '}') end = true;
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

void ESP8266::UartRxISR(){
    char key[10] = "", value[10] = "";
    getFunctionIndex = 1;
    end = false;
    while(getKey(key)){
        getValue(value);
        if(compareString(key, "Kp")) param.Kp = atof(value);
        if(compareString(key, "Ki")) param.Ki = atof(value);
        if(compareString(key, "Kd")) param.Kd = atof(value);
    }
}
