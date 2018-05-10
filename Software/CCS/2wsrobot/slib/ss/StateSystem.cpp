/*
 * StateSystem.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <slib/ss/StateSystem.h>

StateSystem::StateSystem()
{
    // TODO Auto-generated constructor stub
    gy521 = GY521(I2C0);
    gy521.Init();
    kalmanRoll = Kalman();
    time = TIME();
    rollTick = time.tick();
}

StateSystem::~StateSystem()
{
    // TODO Auto-generated destructor stub

}
bool StateSystem::getRoll(float *roll){
    float us;
    float unfilteredRoll;
    float gyro[3];
    gy521.getRoll(&unfilteredRoll);
    gy521.getGyro(gyro);
    us = ((int64_t)time.tick() - (int64_t)rollTick)/time.tickPerUs;
    float s = us/1000000;
    *roll = kalmanRoll.getAngle(unfilteredRoll, gyro[0], s); // Calculate the angle using a Kalman filter
    rollTick = time.tick();
    return true;
}
bool StateSystem::getPitch(float *pitch){
    return true;
}

