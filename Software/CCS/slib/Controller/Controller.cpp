/*
 * Controller.cpp
 *
 *  Created on: Aug 7, 2018
 *      Author: Light
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <slib/Task/Task.h>
#include <slib/Controller/Controller.h>

Controller::Controller(){}
Controller::~Controller(){}

PAV* Controller::pav;
Driver Controller::driver;
PID Controller::pid;

void Controller::init(PAV* _pav){
    pav = _pav;

    driver.init();
    driver.enable();
    pid = PID(pav->controller.pid.KP, pav->controller.pid.KI, pav->controller.pid.KD, pav->controller.pid.MinIpart, pav->controller.pid.MaxIpart, pav->controller.pid.MinUout, pav->controller.pid.MaxUout);

    Task::registerEvent(controllerCallBack, (unsigned long)((1.0/CONTROLLER_CALLBACK_FRQ) * 1000));
}

void Controller::controllerCallBack(){
    pid.setCoeff(pav->controller.pid.KP, pav->controller.pid.KI, pav->controller.pid.KD);
    float dt = 1.0/CONTROLLER_CALLBACK_FRQ;
    float roll = pav->state.altitude.roll;
    float Uout = pid.process(roll, dt);

    pav->controller.pid.Ppart = pid.Ppart;
    pav->controller.pid.Ipart = pid.Ipart;
    pav->controller.pid.Dpart = pid.Dpart;
    pav->controller.pid.Uout  = pid.Uout;

    driver.setVelocityLeft(Uout);
    driver.setVelocityRight(Uout);
}
