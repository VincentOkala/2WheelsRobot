/*
 * PARAMTER.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef SLIB_PARAMETER_PARAMETER_H_
#define SLIB_PARAMETER_PARAMETER_H_

class PARAMETER
{
public:
    PARAMETER();
    virtual ~PARAMETER();

    float Kp;
    float Ki;
    float Kd;
};

#endif /* SLIB_PARAMETER_PARAMETER_H_ */
