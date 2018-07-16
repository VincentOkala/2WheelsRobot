/*
 * Log.h
 *
 *  Created on: Jul 16, 2018
 *      Author: 16138
 */

#ifndef SLIB_LOG_LOG_H_
#define SLIB_LOG_LOG_H_

#include <slib/log/Logger.h>

#include <stdarg.h>
#include <stdint.h>

class Log
{
public:
    Log();
    virtual ~Log();
    static void init(Logger* logger);
    static void logInfo(const char* pcInfo, ...);
    static void logWarning(const char* pcWarn, ...);
    static void logError(const char* pcError, ...);
    static void logStr(const char *str);

private:
    static Logger* logger;
    static void vprintf2(const char *pcString, va_list vaArgP);
};

#endif /* SLIB_LOG_LOG_H_ */
