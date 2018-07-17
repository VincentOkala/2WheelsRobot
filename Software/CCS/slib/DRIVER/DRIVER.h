/*
 * DRIVER.h
 *
 *  Created on: Jun 11, 2018
 *      Author: 16138
 */

#ifndef SLIB_DRIVER_DRIVER_H_
#define SLIB_DRIVER_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#include <modules/DRV8412/DRV8412.h>

class DRIVER
{
public:
    DRIVER();
    virtual ~DRIVER();
    void setVelocityLeft(float duty);
    void setVelocityRight(float duty);
    void disable();
    void enable();
private:
    DRV8412 drv8421;
};

#endif /* SLIB_DRIVER_DRIVER_H_ */
