/*
 * UART.h
 *
 *  Created on: May 9, 2018
 *      Author: light
 */

#ifndef PERIPHERAL_UART_UART_H_
#define PERIPHERAL_UART_UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
// The following are defines for ID of UART modules
//*****************************************************************************
#define UART_0    0
#define UART_1    1
#define UART_2    2
#define UART_3    3
#define UART_4    4
#define UART_5    5
#define UART_6    6
#define UART_7    7

class UART
{
public:
    UART();
    UART(uint8_t UART_, uint32_t BAUDRATE);
    virtual ~UART();
    void send(const char *str);
    void send(const char *str, uint8_t length);
    void reicv(uint8_t *str, uint8_t length);
private:
    uint32_t UART_BASE;
};

#endif /* PERIPHERAL_UART_UART_H_ */
