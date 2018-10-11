/*
 * PARAMTER.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#include <stdio.h>
#include <string.h>

#include <slib/PAV/PAV.h>
#include <slib/Task/Task.h>

PAV::PAV(){}
PAV::~PAV(){}

StatePAV PAV::state;
ControllerPAV PAV::controller;
CC1101 PAV::cc1101;
char PAV::buff[200];

void PAV::init(){
    memset(&state, 0, sizeof(state));
    memset(&controller, 0, sizeof(controller));

    cc1101.init();

    state.COMP_COEFF = 0.98;

    controller.pid.KP = 30;
    controller.pid.KI = 0;
    controller.pid.KD = 0;
    controller.pid.MinIpart = -100;
    controller.pid.MaxIpart = 100;
    controller.pid.MinUout = -100;
    controller.pid.MaxUout = 100;

    Task::registerEvent(PAVLog, 1000.0/PAV_LOG_FRQ);
}

void PAV::PAVLog(){
    sprintf(buff, "-100 %d %d %d %d 100", (uint16_t)controller.pid.Ppart, (uint16_t)controller.pid.Ipart, (uint16_t)controller.pid.Dpart, (uint16_t)controller.pid.Uout);
    cc1101.send((uint8_t*)buff, strlen(buff));
}

