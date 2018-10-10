/*
 * QEI.h
 *
 *  Created on: Aug 11, 2018
 *      Author: 16138
 */

#ifndef PERIPHERAL_QEI_QEI_H_
#define PERIPHERAL_QEI_QEI_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_qei.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/qei.h"

#include <define.h>

typedef enum{
    QEI_0,
    QEI_1
}QEI_;

#define QEI_MAX_POSITION    60000
#define QEI_START_POSITION  (QEI_MAX_POSITION/2)

#define GPIO_PIN_0_QEI_0    GPIO_PIN_6
#define GPIO_PIN_1_QEI_0    GPIO_PIN_7

#define GPIO_PIN_0_QEI_1    GPIO_PIN_5
#define GPIO_PIN_1_QEI_1    GPIO_PIN_6

#define QEI_VELOCITY_FRQ    1000

class QEI
{
public:
    QEI();
    virtual ~QEI();

    QEI(QEI_ QEI_);
    void swap();
    uint32_t getPos();
    int32_t  getDirection();
    uint32_t getVelocity();

    uint32_t QEI_BASE;
};

#endif /* PERIPHERAL_QEI_QEI_H_ */
