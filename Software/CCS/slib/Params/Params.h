/*
 * PARAMTER.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef SLIB_PARAMS_PARAMS_H_
#define SLIB_PARAMS_PARAMS_H_

class Params
{
public:
    Params();
    virtual ~Params();

    float Kp;
    float Ki;
    float Kd;
    float AG_ACC_COEFI;
};

#endif /* SLIB_PARAMS_PARAMS_H_ */
