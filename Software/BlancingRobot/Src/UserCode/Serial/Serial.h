/*
 * Serial.h
 *
 *  Created on: Oct 10, 2019
 *      Author: 16138
 */

#ifndef USERCODE_SERIAL_SERIAL_H_
#define USERCODE_SERIAL_SERIAL_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "usart.h"
#include "circular_buffer/circular_buffer.h"

typedef void (*on_char_recv_cb_t)(const uint8_t);

#define TX_DMA_BUF_SIZE 64
#define RX_DMA_BUF_SIZE	64
#define TX_CIR_BUF_SIZE 64
#define RX_CIR_BUF_SIZE 64

typedef struct{
	// Public elements. Should be changed by user
	UART_HandleTypeDef* huart;

	// Private elements. Should not be changed by user. User to store internal data
	uint8_t tx_dma_buffer[TX_DMA_BUF_SIZE];
	uint8_t rx_dma_buffer[RX_DMA_BUF_SIZE];
	circular_buf_t tx_cbuf_handle;
	uint8_t tx_buf[TX_CIR_BUF_SIZE];
	circular_buf_t rx_cbuf_handle;
	uint8_t rx_buf[RX_CIR_BUF_SIZE];

	bool tx_completed;
	bool rx_completed;

	uint16_t prevCNDTR;
	bool rx_timeout_flag;
}uart_drv_t;

bool uart_init(uart_drv_t* const uart_drv_);

bool uart_send_chr(uart_drv_t* uart_drv, const uint8_t chr);
bool uart_read_chr(uart_drv_t* uart_drv, uint8_t* chr);

bool uart_send(uart_drv_t* uart_drv, const uint8_t* data, const uint16_t len);
bool uart_read(uart_drv_t* const uart_drv, uint8_t* data, uint16_t* len);
bool uart_readline(uart_drv_t* uart_drv, uint8_t* data, uint16_t* len);
bool uart_set_on_char_recv_cb(uart_drv_t* uart_drv, const on_char_recv_cb_t on_char_recv_cb);

bool uart_tx_reset(uart_drv_t* uart_drv);
bool uart_rx_reset(uart_drv_t* uart_drv);

#endif /* USERCODE_SERIAL_SERIAL_H_ */
