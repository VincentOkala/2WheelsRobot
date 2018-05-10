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
#define UART0    0
#define UART1    1
#define UART2    2
#define UART3    3
#define UART4    4
#define UART5    5
#define UART6    6
#define UART7    7

class UART
{
public:
    UART();
    UART(uint8_t ID);
    virtual ~UART();
    bool Init(uint32_t BAUDRATE);
    bool send(const char *str, uint8_t length);
    bool reicv(uint8_t *str, uint8_t length);
private:
    uint32_t SYSCTL_PERIPH_GPIO;
    uint32_t SYSCTL_PERIPH_UART;

    uint32_t GPIO_P_URX;
    uint32_t GPIO_P_UTX;

    uint32_t GPIO_PORT_BASE;
    uint32_t GPIO_PIN_TX;
    uint32_t GPIO_PIN_RX;

    uint32_t UART_BASE;
};

#endif /* PERIPHERAL_UART_UART_H_ */
