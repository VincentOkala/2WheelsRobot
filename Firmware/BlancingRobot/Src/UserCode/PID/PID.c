/*
 * PID.c
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */
#include "math.h"
#include "PID.h"

float pid_compute_angle(pid_params_t *pid_params, float sp, float fb){
	pid_params->sp = sp;
	pid_params->fb = fb;
	pid_params->err = sp-fb;
	if(pid_params->err > M_PI) pid_params->err = pid_params->err-2*M_PI;

	pid_params->P_Part = pid_params->KP*pid_params->err;

	pid_params->I_Part = pid_params->preIPart + pid_params->KI*pid_params->err;
	if(pid_params->I_Part < pid_params->minIpart) pid_params->I_Part = pid_params->minIpart;
	if(pid_params->I_Part > pid_params->maxIPart) pid_params->I_Part = pid_params->maxIPart;
	pid_params->preIPart = pid_params->I_Part;

	if(pid_params->isFistCompute){
		pid_params->preError = pid_params->err;
		pid_params->isFistCompute = false;
	}
	pid_params->D_Part = pid_params->KD*(pid_params->err-pid_params->preError);
	if(pid_params->D_Part < pid_params->minDpart) pid_params->D_Part = pid_params->minDpart;
	if(pid_params->D_Part > pid_params->maxDPart) pid_params->D_Part = pid_params->maxDPart;
	pid_params->preError = pid_params->err;

	pid_params->U = pid_params->P_Part + pid_params->I_Part + pid_params->D_Part;
	if(pid_params->U < pid_params->minOut) pid_params->U = pid_params->minOut;
	if(pid_params->U > pid_params->maxOut) pid_params->U = pid_params->maxOut;

	return pid_params->U;
}

float pid_compute(pid_params_t *pid_params, float sp, float fb){

	pid_params->sp = sp;
	pid_params->fb = fb;
	pid_params->err = sp-fb;


	pid_params->P_Part = pid_params->KP*pid_params->err;

	pid_params->I_Part = pid_params->preIPart + pid_params->KI*pid_params->err;
	if(pid_params->I_Part < pid_params->minIpart) pid_params->I_Part = pid_params->minIpart;
	if(pid_params->I_Part > pid_params->maxIPart) pid_params->I_Part = pid_params->maxIPart;
	pid_params->preIPart = pid_params->I_Part;

	if(pid_params->isFistCompute){
		pid_params->preError = pid_params->err;
		pid_params->isFistCompute = false;
	}
	pid_params->D_Part = pid_params->KD*(pid_params->err-pid_params->preError);
	if(pid_params->D_Part < pid_params->minDpart) pid_params->D_Part = pid_params->minDpart;
	if(pid_params->D_Part > pid_params->maxDPart) pid_params->D_Part = pid_params->maxDPart;
	pid_params->preError = pid_params->err;

	pid_params->U = pid_params->P_Part + pid_params->I_Part + pid_params->D_Part;
	if(pid_params->U < pid_params->minOut) pid_params->U = pid_params->minOut;
	if(pid_params->U > pid_params->maxOut) pid_params->U = pid_params->maxOut;

	return pid_params->U;
}

void pid_reset(pid_params_t *pid_params){
	pid_params->isFistCompute = true;
	pid_params->preIPart = 0;
	pid_params->preError = 0;
}
