/*
 * Com.h
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#ifndef USERCODE_COM_COM_H_
#define USERCODE_COM_COM_H_

#include "UserCode/Serial/Serial.h"

typedef void (*on_mav_recv_t)();

void com_init();
void set_on_mav_recv(on_mav_recv_t on_mav_recv);

#endif /* USERCODE_COM_COM_H_ */
