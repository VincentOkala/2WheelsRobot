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
	pid_params_t pid_whe0;
	pid_params_t pid_whe1;
	pid_params_t pid_sta;
	pid_params_t pid_rob;
	float believe_in_gyro;
	float angle_ajusted; // Calibrated vertical angle in earth frame
	int32_t gx_offset;
	int32_t gy_offset;
	int32_t gz_offset;
}params_t;

extern params_t params;

void params_save();
bool params_load();

#endif /* USERCODE_PARAMS_PARAMS_H_ */
