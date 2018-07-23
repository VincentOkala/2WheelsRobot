/*
 * Console.h
 *
 *  Created on: May 9, 2018
 *      Author: light
 */

#ifndef MODULES_Console_Console_H_
#define MODULES_Console_Console_H_

#include <stdbool.h>
#include <stdint.h>

#include <peripheral/UART/UART.h>

class Console
{
public:
    Console();
    virtual ~Console();
    static void init();
    static void gets(uint8_t *str, uint8_t length);
    static void printf(const char *pcString, ...);
private:
    static UART uart;
    static void UARTvprintf(const char *pcString, va_list vaArgP);

};

#endif /* MODULES_Console_Console_H_ */
