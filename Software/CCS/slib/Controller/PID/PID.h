/*
 * pid.h
 *
 *  Created on: Jul 25, 2018
 *      Author: 16138
 */

#ifndef SLIB_CONTROLLER_PID_PID_H_
#define SLIB_CONTROLLER_PID_PID_H_

class PID
{
public:
    PID();
    PID( float _kp, float _ki, float _kd, float _minI, float _maxI, float _minOut, float _maxOut);
    void setCoeff( float _kp, float _ki, float _kd);
    virtual ~PID();
    float process(float newState, float dt);

    float Ppart;
    float Ipart;
    float Dpart;

    float Uout;

private:
    float kp;
    float ki;
    float kd;
    float minI;
    float maxI;
    float minOut;
    float maxOut;

    float pre_err;
    float pre_pre_err;
    float pre_Uout;
};

#endif /* SLIB_CONTROLLER_PID_PID_H_ */
