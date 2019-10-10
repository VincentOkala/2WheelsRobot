/*
 * Mode_Basic.h
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#ifndef USERCODE_MODE_BASIC_MODE_BASIC_H_
#define USERCODE_MODE_BASIC_MODE_BASIC_H_

#include "UserCode/Mav/protocol/mavlink.h"
#include "UserCode/user_define.h"

void mode_basic_init();
void mode_basic_deinit();
void on_mode_basic_mavlink_recv(mavlink_message_t *msg);

#endif /* USERCODE_MODE_BASIC_MODE_BASIC_H_ */
