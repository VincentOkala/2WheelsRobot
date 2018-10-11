/*
 * PARAMTER.h
 *
 *  Created on: Jun 12, 2018
 *      Author: 16138
 */

#ifndef SLIB_PAV_PAV_H_
#define SLIB_PAV_PAV_H_

#include <stdio.h>
#include <stdint.h>

#include <modules/CC1101/CC1101.h>

#define PAV_LOG_FRQ     50

typedef struct{
    float roll;
    float pitch;
    float yaw;
}Altitude;

typedef struct{
    float COMP_COEFF;
    Altitude altitude;
}StatePAV;

typedef struct{
    float KP;
    float KI;
    float KD;
    float MinIpart;
    float MaxIpart;
    float MinUout;
    float MaxUout;
    float Ppart;
    float Ipart;
    float Dpart;
    float Uout;
}Pid;

typedef struct{
    Pid pid;

}ControllerPAV;

class PAV
{
public:
    PAV();
    virtual ~PAV();
    void init();
    static StatePAV state;
    static ControllerPAV controller;
    static CC1101 cc1101;
private:
    static void PAVLog();
    static char buff[200];
};

#endif /* SLIB_PAV_PAV_H_ */
