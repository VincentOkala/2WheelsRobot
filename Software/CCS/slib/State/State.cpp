/*
 * State.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <slib/Log/Log.h>
#include <slib/State/State.h>
#include <slib/Task/Task.h>

State::State(){}
State::~State(){}

GY521 State::gy521;
GPIO State::portF;
PAV* State::pav;

void State::init(PAV* _pav){

    pav = _pav;

    gy521.init();
    portF = GPIO(GPIO_PORT_F);

    portF.mode(GPIO_PIN_1, GPIO_MODE_OUTPUT);
    portF.mode(GPIO_PIN_2, GPIO_MODE_OUTPUT);

    Task::registerEvent(stateUpdateTask, (unsigned long)((1.0/STATE_UPDATE_FREQ) * 1000));
}

void State::stateUpdateTask(void){
    float accRoll;
    float gyro[3];

    accRoll = gy521.getRoll();
    gy521.getGyro(gyro);

    float comp_coef = pav->state.COMP_COEFF;
    float roll = pav->state.altitude.roll;
    roll = comp_coef * (roll + gyro[1] * 1.0/STATE_UPDATE_FREQ) + (1-comp_coef) * accRoll;

    if(roll > 0){
        portF.write(GPIO_PIN_1, VALUE_ON);
        portF.write(GPIO_PIN_2, VALUE_OFF);
    }
    else{
        portF.write(GPIO_PIN_1, VALUE_OFF);
        portF.write(GPIO_PIN_2, VALUE_ON);
    }
    pav->state.altitude.roll = roll;
}

