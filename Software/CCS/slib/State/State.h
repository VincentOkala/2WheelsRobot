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
#include "../PAV/PAV.h"

#define STATE_UPDATE_FREQ     100

class State
{
public:
    State();
    virtual ~State();

    void init(PAV* _pav);
    float getRoll();

private:
    static GY521 gy521;
    static GPIO portF;
    static PAV* pav;

    static void stateUpdateTask(void);
};

#endif /* SLIB_State_H_ */
