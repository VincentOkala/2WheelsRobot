/*
 * pid.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: 16138
 */

#include <slib/Controller/PID/PID.h>

PID::PID(){}
PID::~PID(){}

PID::PID( float _kp, float _ki, float _kd, float _minI, float _maxI, float _minOut, float _maxOut):
        kp(_kp),ki(_ki),kd(_kd),minI(_minI),maxI(_maxI),minOut(_minOut),maxOut(_maxOut)
{
    Ppart = 0;
    Ipart = 0;
    Dpart = 0;

    pre_err = 0;

    Uout = 0;
}

float PID::process(float err, float dt){

    Ppart = kp * err;

    Ipart = ki * err * dt;
    Ipart = Ipart > minI ? Ipart : minI;
    Ipart = Ipart < maxI ? Ipart : maxI;

    Dpart = kd * (err - pre_err) * dt;
    pre_err = err;

    Uout = Ppart + Ipart + Dpart;
    Uout = Uout > minOut ? Uout : minOut;
    Uout = Uout < maxOut ? Uout : maxOut;

    return Uout;
}

void PID::setCoeff( float _kp, float _ki, float _kd){
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

