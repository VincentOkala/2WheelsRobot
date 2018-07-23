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
#include <slib/Params/Params.h>

#define UPDATE_FREQ     100

class StateSystem
{
public:
    StateSystem(Params* params);
    virtual ~StateSystem();

    float getRoll();

private:
    static GY521 gy521;
    static GPIO portF;

    static float roll;
    static void stateUpdateTask(void);
    static Params* params;
};

#endif /* SLIB_STATESYSTEM_H_ */
