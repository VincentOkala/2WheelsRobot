/*
 * Logger.h
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#ifndef SLIB_LOG_LOGGER_H_
#define SLIB_LOG_LOGGER_H_

#include <stdint.h>

class Logger
{
public:
    Logger();
    virtual ~Logger();
    void init();
    void write(const char* str);
    void write(const char* str, uint8_t length);
};

#endif /* SLIB_LOG_LOGGER_H_ */
