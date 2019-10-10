/*
 * Com.c
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#include "Com.h"
#include "usart.h"
#include "UserCode/user_define.h"

static uart_drv_t uart_drv = {
		.huart = &COM_USART
};

void com_init(){
	uart_init(&uart_drv);
}

void set_on_mav_recv(on_mav_recv_t on_mav_recv){

}
