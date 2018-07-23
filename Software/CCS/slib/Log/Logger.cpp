/*
 * Logger.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#include <slib/Log/Logger.h>

UART Logger::uart;

Logger::Logger()
{
    // TODO Auto-generated constructor stub
    uart = UART(UART_0, 115200);
}

Logger::~Logger()
{
    // TODO Auto-generated destructor stub
}

void Logger::write(const char* str){
    uart.send(str);
}
void Logger::write(const char* str, uint8_t length){
    uart.send(str, length);
}
