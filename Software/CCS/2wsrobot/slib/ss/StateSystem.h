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
#include "../ss/kf/kf.h"
#include <peripheral/TIME/TIME.h>

class StateSystem
{
public:
    StateSystem();
    virtual ~StateSystem();
    bool getRoll(float *roll);
    bool getPitch(float *pitch);
private:
    GY521 gy521;
    Kalman kalmanRoll;
    TIME time;

    uint32_t rollTick;
};

#endif /* SLIB_STATESYSTEM_H_ */
