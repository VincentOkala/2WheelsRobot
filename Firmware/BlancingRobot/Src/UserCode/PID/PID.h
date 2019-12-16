/*
 * PID.h
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#ifndef USERCODE_PID_PID_H_
#define USERCODE_PID_PID_H_

#include <stdbool.h>

typedef struct{
	// Public variables
	float KP;
	float KI;
	float KD;

	// Private parameters
	float minIpart;
	float maxIPart;
	float minDpart;
	float maxDPart;
	float minOut;
	float maxOut;

	// Private variables
	float preIPart;
	float preError;
	bool isFistCompute;
}pid_params_t;

float pid_compute(pid_params_t *pid_params, float error);
void pid_reset(pid_params_t *pid_params);

#endif /* USERCODE_PID_PID_H_ */
