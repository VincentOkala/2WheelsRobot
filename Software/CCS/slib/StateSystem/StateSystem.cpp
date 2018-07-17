/*
 * StateSystem.cpp
 *
 *  Created on: May 10, 2018
 *      Author: light
 */

#include <slib/StateSystem/StateSystem.h>
#include <slib/log/Log.h>

GY521 StateSystem::gy521 = GY521(I2C_1, GYRO_SCALE_250, ACCEL_SCALE_2G);
GPIO  StateSystem::portF = GPIO(PORTF);
float StateSystem::roll = 0;

StateSystem::StateSystem()
{
    // TODO Auto-generated constructor stub
    Log::logDoing("Initialize State System ");

    timer3 = TIMER(TIMER_3, 100);

    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_BOTH, StateSystem::timer3ISR);

    portF.mode(GPIO_PIN_1, MODE_OUTPUT);
    portF.mode(GPIO_PIN_2, MODE_OUTPUT);

    Log::logDone("Initialize State System");

}

StateSystem::~StateSystem()
{
    // TODO Auto-generated destructor stub

}

float StateSystem::getRoll(){
    return roll;
}

void StateSystem::timer3ISR(void){
    float accRoll;
    float gyro[3];
    uint32_t flag = TimerIntStatus(TIMER3_BASE, true);
    TimerIntClear(TIMER3_BASE, flag);

    accRoll = gy521.getRoll();
    gy521.getGyro(gyro);

    roll = 0.90 * (roll + gyro[0] * 0.01) + 0.1 * accRoll;

    if(roll > 0){
        portF.write(GPIO_PIN_1, VALUE_ON);
        portF.write(GPIO_PIN_2, VALUE_OFF);
    }
    else{
        portF.write(GPIO_PIN_1, VALUE_OFF);
        portF.write(GPIO_PIN_2, VALUE_ON);
    }
}

