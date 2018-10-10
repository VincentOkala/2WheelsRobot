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
typedef enum{
    UART_0,
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7
}UART_;


class UART
{
public:
    UART();
    UART(UART_ UART_, uint32_t BAUDRATE);
    virtual ~UART();
    void send(const char *str);
    void send(const char *str, uint8_t length);
    void reicv(uint8_t *str, uint8_t length);
    uint8_t reicv(uint8_t *str, char delimiter);

    uint32_t UART_BASE;
    uint32_t INT_UART;
};

#endif /* PERIPHERAL_UART_UART_H_ */
