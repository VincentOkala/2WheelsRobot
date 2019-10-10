/*
 * Com.h
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#ifndef USERCODE_COM_COM_H_
#define USERCODE_COM_COM_H_

#include "UserCode/Serial/Serial.h"
#include "UserCode/Mav/protocol/mavlink.h"

typedef void (*on_mav_recv_t)(mavlink_message_t*);

void com_init();
void com_set_on_mav_recv(on_mav_recv_t on_mav_recv);
void com_send(uint8_t *data, uint16_t len);

#endif /* USERCODE_COM_COM_H_ */
