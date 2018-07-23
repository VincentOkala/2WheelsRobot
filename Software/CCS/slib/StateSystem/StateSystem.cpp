/*
 * StateSystem.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <slib/Log/Log.h>
#include <slib/StateSystem/StateSystem.h>
#include <slib/Task/Task.h>

GY521 StateSystem::gy521;
GPIO  StateSystem::portF;
float StateSystem::roll = 0;
Params* StateSystem::params;

StateSystem::StateSystem(Params* params)
{
    // TODO Auto-generated constructor stub
    Log::logDoing("Initialize State System ");
    this->params = params;

    gy521 = GY521(I2C_1, GYRO_SCALE_250, ACCEL_SCALE_2G);
    portF = GPIO(PORTF);

    portF.mode(GPIO_PIN_1, MODE_OUTPUT);
    portF.mode(GPIO_PIN_2, MODE_OUTPUT);

    Task::registerEvent(StateSystem::stateUpdateTask, (unsigned long)((1.0/UPDATE_FREQ) * 1000));

    Log::logDone("Initialize State System");

}

StateSystem::~StateSystem()
{
    // TODO Auto-generated destructor stub

}

float StateSystem::getRoll(){
    return roll;
}

void StateSystem::stateUpdateTask(void){
    float accRoll;
    float gyro[3];

    accRoll = gy521.getRoll();
    gy521.getGyro(gyro);

    roll = params->AG_ACC_COEFI * (roll + gyro[0] * 0.01) + (1-params->AG_ACC_COEFI) * accRoll;

    if(roll > 0){
        portF.write(GPIO_PIN_1, VALUE_ON);
        portF.write(GPIO_PIN_2, VALUE_OFF);
    }
    else{
        portF.write(GPIO_PIN_1, VALUE_OFF);
        portF.write(GPIO_PIN_2, VALUE_ON);
    }
}

