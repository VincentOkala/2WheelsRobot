/*
 * Logger.h
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#ifndef SLIB_LOG_LOGGER_H_
#define SLIB_LOG_LOGGER_H_

#include <stdint.h>

#include <peripheral/UART/UART.h>

class Logger
{
public:
    Logger();
    virtual ~Logger();
    void write(const char* str);
    void write(const char* str, uint8_t length);
private:
    static UART uart;
};

#endif /* SLIB_LOG_LOGGER_H_ */
