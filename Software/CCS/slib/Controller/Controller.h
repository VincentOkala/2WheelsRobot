/*
 * Controller.h
 *
 *  Created on: Aug 7, 2018
 *      Author: Light
 */

#ifndef SLIB_CONTROLLER_CONTROLLER_H_
#define SLIB_CONTROLLER_CONTROLLER_H_

#include <stdio.h>
#include <stdint.h>

#include <define.h>

#include <slib/Driver/Driver.h>
#include <slib/Controller/PID/PID.h>
#include <slib/PAV/PAV.h>

#define CONTROLLER_CALLBACK_FRQ 100

class Controller
{
public:
    Controller();
    virtual ~Controller();
    void init(PAV* _pav);
private:
    static PAV* pav;
    static Driver driver;
    static PID pid;

    static void controllerCallBack();
};

#endif /* SLIB_CONTROLLER_CONTROLLER_H_ */
