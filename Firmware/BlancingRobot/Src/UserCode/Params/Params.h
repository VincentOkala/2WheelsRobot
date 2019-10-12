/*
 * Params.h
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#ifndef USERCODE_PARAMS_PARAMS_H_
#define USERCODE_PARAMS_PARAMS_H_

#include "UserCode/PID/PID.h"

typedef struct{
	pid_params_t pid_params;
	float believe_in_gyro;
}params_t;

extern params_t params;

#endif /* USERCODE_PARAMS_PARAMS_H_ */
