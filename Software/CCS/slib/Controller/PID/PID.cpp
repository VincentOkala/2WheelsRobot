/*
 * pid.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: 16138
 */

#include <slib/Controller/PID/PID.h>

PID::PID()
{
    // TODO Auto-generated constructor stub
}

PID::PID( float _kp, float _ki, float _kd, float _minI, float _maxI, float _minOut, float _maxOut)
{
    // TODO Auto-generated constructor stub
    kp = _kp;
    ki = _ki;
    kd = _kd;
    minI = _minI;
    maxI = _maxI;
    minOut = _minOut;
    maxOut = _maxOut;

    pre_err = 0;
    pre_pre_err = 0;

    Ppart = 0;
    Ipart = 0;
    Dpart = 0;

    Uout = 0;
    pre_Uout = 0;
}

PID::~PID()
{
    // TODO Auto-generated destructor stub
}

float PID::process(float err, float dt){

    Ppart = kp * err;
    //Ppart = kp * (err - pre_err);

    Ipart = ki * dt / 2 * (err + pre_err);
    Ipart = Ipart > minI ? Ipart : minI;
    Ipart = Ipart < maxI ? Ipart : maxI;
    if(ki == 0) Ipart = 0;

    Dpart = kd / dt * (err - 2*pre_err + pre_pre_err);
    if(kd == 0) Dpart = 0;
    pre_pre_err = pre_err;
    pre_err = err;

    Uout = pre_Uout + Ppart + Ipart + Dpart;
    Uout = Uout > minOut ? Uout : minOut;
    Uout = Uout < maxOut ? Uout : maxOut;
    pre_Uout = Uout;
    return Uout;
}

void PID::setCoeff( float _kp, float _ki, float _kd){
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

