/*
 * PARAMTER.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#include <stdio.h>
#include <string.h>

#include <slib/PAV/PAV.h>

PAV::PAV(){}
PAV::~PAV(){}

void PAV::init(){
    memset(&state, 0, sizeof(state));
    memset(&controller, 0, sizeof(controller));

    state.COMP_COEFF = 0.98;

    controller.pid.KP = 30;
    controller.pid.KI = 0;
    controller.pid.KD = 0;
    controller.pid.MinIpart = -100;
    controller.pid.MaxIpart = 100;
    controller.pid.MinUout = -100;
    controller.pid.MaxUout = 100;

}

