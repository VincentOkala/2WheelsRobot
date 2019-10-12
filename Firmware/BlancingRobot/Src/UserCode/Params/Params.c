/*
 * Params.c
 *
 *  Created on: Oct 12, 2019
 *      Author: 16138
 */

#include "Params.h"

params_t params = {
		.pid_params = {
				.KP = 10,
				.KI = 0.1,
				.KD = 0,
				.preIPart = 0,
				.preError = 0,
				.minIpart = -500,
				.maxIPart = 500,
				.minDpart = -500,
				.maxDPart = 500,
				.minOut = -1000,
				.maxOut = 1000,
				.isFistCompute = true
		},
		.believe_in_gyro = 0.98
};
