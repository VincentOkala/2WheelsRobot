#include "Serial.h"
#include "UserCode/Timer/timer.h"

#define CIRCULAR_BUFFER_FULL_TIMEOUT	5
static uart_drv_t* uart_drv;


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == uart_drv->huart->Instance){
		uart_drv->tx_completed = true;
	}
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == uart_drv->huart->Instance){
	    uint16_t i, start, length;
	    uint16_t currCNDTR = __HAL_DMA_GET_COUNTER(huart->hdmarx);

	    /* Ignore IDLE Timeout when the received characters exactly filled up the DMA buffer and DMA Rx Complete IT is generated, but there is no new character during timeout */
	    if(uart_drv->rx_timeout_flag && currCNDTR == sizeof(uart_drv->rx_dma_buffer))
	    {
	    	uart_drv->rx_timeout_flag = false;
	        return;
	    }

	    /* Determine start position in DMA buffer based on previous CNDTR value */
	    start = (uart_drv->prevCNDTR < sizeof(uart_drv->rx_dma_buffer)) ? ( sizeof(uart_drv->rx_dma_buffer) - uart_drv->prevCNDTR) : 0;

	    if(uart_drv->rx_timeout_flag)    /* Timeout event */
	    {
	        /* Determine new data length based on previous DMA_CNDTR value:
	         *  If previous CNDTR is less than DMA buffer size: there is old data in DMA buffer (from previous timeout) that has to be ignored.
	         *  If CNDTR == DMA buffer size: entire buffer content is new and has to be processed.
	        */
	        length = (uart_drv->prevCNDTR < sizeof(uart_drv->rx_dma_buffer)) ? (uart_drv->prevCNDTR - currCNDTR) : (sizeof(uart_drv->rx_dma_buffer) - currCNDTR);
	        uart_drv->prevCNDTR = currCNDTR;
	        uart_drv->rx_timeout_flag = false;
	    }
	    else                /* DMA Rx Complete event */
	    {
	        length = sizeof(uart_drv->rx_dma_buffer) - start;
	        uart_drv->prevCNDTR = sizeof(uart_drv->rx_dma_buffer);
	    }

	    /* Change the previous remaining data unit to current remaining data unit */
	    uart_drv->prevCNDTR = currCNDTR;

	    /* Copy and Process new data */
	    for(i=start; i<start+length; i++)
	    {
	    	circular_buf_put(&uart_drv->rx_cbuf_handle, uart_drv->rx_dma_buffer[i]);
	    }
	}
}

void uart_cb()
{
	if(uart_drv->tx_completed){
		size_t size = circular_buf_size(&uart_drv->tx_cbuf_handle);
		if(size > sizeof(uart_drv->tx_dma_buffer)) size = sizeof(uart_drv->tx_dma_buffer);
		if(size != 0){
			for(size_t i = 0; i < size; i++){
				circular_buf_get(&uart_drv->tx_cbuf_handle, &uart_drv->tx_dma_buffer[i]);
			}
			uart_drv->tx_completed = false;
			HAL_UART_Transmit_DMA(uart_drv->huart, uart_drv->tx_dma_buffer, size);
		}
	}

    uart_drv->rx_timeout_flag = true;
    uart_drv->huart->hdmarx->XferHalfCpltCallback(uart_drv->huart->hdmarx);
}

/**
 * @brief Init uart interface
 * 
 * @param uart_drv
 * @return drv_stt_t 
 */
bool uart_init(uart_drv_t* const uart_drv_){
	uart_drv = uart_drv_;

	// Init uart interface using hal
	HAL_UART_MspInit(uart_drv->huart);

	// Init circular buffer for uart driver
	circular_buf_init(&uart_drv->tx_cbuf_handle, uart_drv->tx_buf, sizeof(uart_drv->tx_buf));
	circular_buf_init(&uart_drv->rx_cbuf_handle, uart_drv->rx_buf, sizeof(uart_drv->rx_buf));

	uart_drv->prevCNDTR =  sizeof(uart_drv->rx_buf);
	uart_drv->rx_timeout_flag = false;
	HAL_UART_Receive_DMA(uart_drv->huart, (uint8_t*)uart_drv->rx_dma_buffer, sizeof(uart_drv->rx_dma_buffer));


	timer_register_callback(uart_cb, 20, 0, TIMER_MODE_REPEAT);
	return true;
}

bool uart_send(uart_drv_t* uart_drv, const uint8_t* data, const uint16_t len){
	for(uint16_t i=0; i<len; i++){
		bool drv_stt = uart_send_chr(uart_drv, data[i]);
		if(drv_stt != true) return drv_stt;
	}
	return true;
}

bool uart_read(uart_drv_t* uart_drv, uint8_t* data, uint16_t* len){
	for(uint16_t i=0; i<*len; i++){
		bool drv_stt = uart_read_chr(uart_drv, data + i);
		if(drv_stt != true){
			*len = i+1;
			return drv_stt;
		}
	}
	return true;
}

bool uart_readline(uart_drv_t* uart_drv, uint8_t* data, uint16_t* len){
	uint16_t i = 0;
	uint8_t chr;
	uint8_t cnt = 0;
	while(true){
		if(uart_read_chr(uart_drv, &chr) == true){
			if(chr != '\r' && chr != '\n'){
				data[i] = chr;
				i++;
			}
			else if(chr == '\n' && i==0) continue;
			else{
				data[i] = '\r';
				data[i+1] = '\n';
				data[i+2] = 0;
				*len = i + 2;
				return true;
			}
		}
		else{
			if(cnt == 100) break;
			cnt++;
			HAL_Delay(10);
		}
	}
	return true;
}

bool uart_send_chr(uart_drv_t* const uart_drv, const uint8_t chr){
	if(circular_buf_put(&uart_drv->tx_cbuf_handle, chr)){
		return false;
	}
	return true;
}

bool uart_read_chr(uart_drv_t* uart_drv, uint8_t* chr){
	if(circular_buf_get(&uart_drv->rx_cbuf_handle, chr)){
		return false;
	}
	return true;
}

bool uart_tx_reset(uart_drv_t* uart_drv){
	circular_buf_reset(&uart_drv->tx_cbuf_handle);
	return true;
}
bool uart_rx_reset(uart_drv_t* uart_drv){
	circular_buf_reset(&uart_drv->rx_cbuf_handle);
	return true;
}
