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

void Controller::init(PAV* _pav){
    pav = _pav;

    driver.init();
    driver.enable();

    Task::registerEvent(controllerCallBack, (unsigned long)((1.0/CONTROLLER_CALLBACK_FRQ) * 1000));
}

void Controller::controllerCallBack(){
    driver.setVelocityLeft(50);
    driver.setVelocityRight(50);
}
