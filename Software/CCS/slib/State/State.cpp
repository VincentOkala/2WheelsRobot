/*
 * State.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <slib/Log/Log.h>
#include <slib/State/State.h>
#include <slib/Task/Task.h>

GY521 State::gy521;
GPIO  State::portF;
float State::roll = 0;
Params* State::params;
Kalman State::kalman = Kalman();

State::State(Params* params)
{
    // TODO Auto-generated constructor stub
    Log::logDoing("Initialize State System ");
    this->params = params;

    gy521 = GY521();
    portF = GPIO(GPIO_PORT_F);

    portF.mode(GPIO_PIN_1, GPIO_MODE_OUTPUT);
    portF.mode(GPIO_PIN_2, GPIO_MODE_OUTPUT);

    Task::registerEvent(State::stateUpdateTask, (unsigned long)((1.0/UPDATE_FREQ) * 1000));

    Log::logDone("Initialize State System");

}

State::~State()
{
    // TODO Auto-generated destructor stub

}

float State::getRoll(){
    return roll;
}

void State::stateUpdateTask(void){
    float accRoll;
    float gyro[3];

    accRoll = gy521.getRoll();
    gy521.getGyro(gyro);

    // roll = params->AG_ACC_COEFI * (roll + gyro[0] * 0.01) + (1-params->AG_ACC_COEFI) * accRoll;
    kalman.getAngle(accRoll, gyro[0], 0.01);

    if(roll > 0){
        portF.write(GPIO_PIN_1, VALUE_ON);
        portF.write(GPIO_PIN_2, VALUE_OFF);
    }
    else{
        portF.write(GPIO_PIN_1, VALUE_OFF);
        portF.write(GPIO_PIN_2, VALUE_ON);
    }
}

