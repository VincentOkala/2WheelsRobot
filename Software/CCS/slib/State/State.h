/*
 * State.h
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#ifndef SLIB_State_H_
#define SLIB_State_H_

#include <stdint.h>
#include <stdbool.h>

#include <modules/GY521/GY521.h>
#include <peripheral/GPIO/GPIO.h>
#include <slib/Params/Params.h>
#include "../../peripheral/GPTM/GPTM.h"
#include "../State/Kalman/Kalman.h"

#define UPDATE_FREQ     100

class State
{
public:
    State(Params* params);
    virtual ~State();

    float getRoll();

private:
    static GY521 gy521;
    static GPIO portF;

    static float roll;
    static void stateUpdateTask(void);
    static Params* params;

    static Kalman kalman;
};

#endif /* SLIB_State_H_ */
