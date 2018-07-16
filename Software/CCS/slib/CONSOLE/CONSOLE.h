/*
 * CONSOLE.h
 *
 *  Created on: May 9, 2018
 *      Author: light
 */

#ifndef MODULES_CONSOLE_CONSOLE_H_
#define MODULES_CONSOLE_CONSOLE_H_

#include <stdbool.h>
#include <stdint.h>

#include <peripheral/UART/UART.h>

class CONSOLE
{
public:
    CONSOLE();
    virtual ~CONSOLE();
    static bool gets(uint8_t *str, uint8_t length);
    static bool printf(const char *pcString, ...);
private:
    static UART uart;
    static void UARTvprintf(const char *pcString, va_list vaArgP);

};

#endif /* MODULES_CONSOLE_CONSOLE_H_ */
