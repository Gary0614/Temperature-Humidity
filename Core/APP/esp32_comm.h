#ifndef __ESP32_COMM_H_
#define __ESP32_COMM_H_

#include "usart.h"
#include "string.h"
#include "myuart.h"
#include "led_task.h"

#define uart1	huart1
extern DMA_HandleTypeDef hdma_usart1_rx;

#define RX_BUF_ACK_MAX	20
#define RETRY_MAX	3
#define ACK_WAIT_MAX	500


extern LED_TaskCtx_t LED_run_t;

// ESP32 模块状态


typedef enum {
	COMM_IDLE = 0,
//	COMM_SEND,
	COMM_WAIT_ACK,
//	COMM_SUCCESS,
//	COMM_RETRY,
	COMM_ERROR
}comm_state_t;

typedef struct{
	comm_state_t	state;
//	sample_rate		rate;

	uint8_t 		retry_cnt;
//	uint8_t 		last_sample_tick;
	uint8_t			ack_start_tick;

	uint8_t			esp32_online;
}esp32_state_t;

void ESP32_Init(esp32_state_t* esp32_t);
void ESP32_Task(esp32_state_t* esp32_t);

#endif
