/*
 * PARAMTER.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef SLIB_PAV_PAV_H_
#define SLIB_PAV_PAV_H_

typedef struct{
    float roll;
    float pitch;
    float yaw;
}Altitude;

typedef struct{
    float COMP_COEFF;
    Altitude altitude;
}StatePAV;

class PAV
{
public:
    PAV();
    virtual ~PAV();
    void init();
    StatePAV state;
};

#endif /* SLIB_PAV_PAV_H_ */
