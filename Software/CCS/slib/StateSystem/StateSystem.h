/*
 * StateSystem.h
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#ifndef SLIB_STATESYSTEM_H_
#define SLIB_STATESYSTEM_H_

#include <stdint.h>
#include <stdbool.h>

#include <modules/GY521/GY521.h>
#include <peripheral/GPIO/GPIO.h>
#include "../../peripheral/Timer/TIMER.h"

#define UPDATE_FREQ     100

class StateSystem
{
public:
    StateSystem();
    virtual ~StateSystem();

    float getRoll();

private:
    static GY521 gy521;
    static GPIO portF;

    TIMER timer3;

    static float roll;
    static void timer3ISR(void);
};

#endif /* SLIB_STATESYSTEM_H_ */
