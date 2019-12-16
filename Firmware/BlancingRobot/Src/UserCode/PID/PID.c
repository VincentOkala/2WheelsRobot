/*
 * PID.c
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */
#include "PID.h"
float pid_compute(pid_params_t *pid_params, float error){

	float P_part = pid_params->KP*error;

	float I_part = pid_params->preIPart + pid_params->KI*error;
	if(I_part < pid_params->minIpart) I_part = pid_params->minIpart;
	if(I_part > pid_params->maxIPart) I_part = pid_params->maxIPart;
	pid_params->preIPart = I_part;

	if(pid_params->isFistCompute){
		pid_params->preError = error;
		pid_params->isFistCompute = false;
	}
	float D_part = pid_params->KD*(error-pid_params->preError);
	if(D_part < pid_params->minDpart) D_part = pid_params->minDpart;
	if(D_part > pid_params->maxDPart) D_part = pid_params->maxDPart;
	pid_params->preError = error;

	float out = P_part + I_part + D_part;
	if(out < pid_params->minOut) out = pid_params->minOut;
	if(out > pid_params->maxOut) out = pid_params->maxOut;

	return out;
}

void pid_reset(pid_params_t *pid_params){
	pid_params->isFistCompute = true;
	pid_params->preIPart = 0;
	pid_params->preError = 0;
}
