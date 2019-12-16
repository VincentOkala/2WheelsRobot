/*
 * Params.h
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#ifndef USERCODE_PARAMS_PARAMS_H_
#define USERCODE_PARAMS_PARAMS_H_

#include <stdint.h>
#include "UserCode/PID/PID.h"

typedef struct{
	pid_params_t pid_params;
	float believe_in_gyro;
	float stand_point;
	int32_t gx_offset;
	int32_t gy_offset;
	int32_t gz_offset;
}params_t;

extern params_t params;

void params_save();
bool params_load();

#endif /* USERCODE_PARAMS_PARAMS_H_ */
