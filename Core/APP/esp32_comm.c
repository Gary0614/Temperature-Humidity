/*
 * esp32_comm.c
 *
 *  Created on: Jan 22, 2026
 *      Author: lll
 */


#include "esp32_comm.h"


//esp32_state_t esp32_1;
uint8_t rxdata_ACK[RX_BUF_ACK_MAX];

void ESP32_Init(esp32_state_t* esp32_t)
{
	esp32_t->state = COMM_IDLE;
	esp32_t->esp32_online = 1;
	esp32_t->retry_cnt = 0;
	esp32_t->ack_start_tick = HAL_GetTick();
}


void ESP32_Task(esp32_state_t* esp32_t)
{
	if(esp32_t->state == COMM_IDLE)
	{
		// comm_state_t IDLE 时 send 数据
		Uart_CmdGetTemp();

		//Send 之后等待 ACK 并且启动 ACK 超时时间. 状态更新为：COMM_WAIT_ACK
		esp32_t->state = COMM_WAIT_ACK;
		esp32_t->ack_start_tick = HAL_GetTick();
	}
	else if(esp32_t->state == COMM_WAIT_ACK){
		//状态更新为：COMM_WAIT_ACK 成功接收 ACK 就更新状态 success, 超时就 retry
		HAL_UARTEx_ReceiveToIdle_DMA(&uart1, rxdata_ACK, sizeof(rxdata_ACK));
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
		if(strcmp((char*)rxdata_ACK,"$DATA:ACK#") == 0)
		{
			//更新状态为：success

			esp32_t->state = COMM_IDLE;
		}else if(esp32_t->retry_cnt < RETRY_MAX){
			if(HAL_GetTick() - esp32_t->ack_start_tick > ACK_WAIT_MAX)
			{
				esp32_t->retry_cnt++;
			}
		}else {
			//降低速率

			//输出错误
			UART_SendString("ERROR: ESP32 RETURN ACK!!");
		}

	}
	else if(esp32_t->state == COMM_ERROR){
		LED_Task_SetError(&LED_run_t, 5);
	}
}




// Send 之后等待 ACK 并且启动 ACK 超时时间. 状态更新为：COMM_WAIT_ACK 成功接收 ACK 就更新状态 success, 超时就 retry

// success 就继续上传

/*
 * 如果超时未接收
if (HAL_GetTick() - ack_start_tick > ACK_TIMEOUT)
{
    comm_state = COMM_RETRY;
}

// 记录 retry 次数。 retry_cnt 变量.
 * if retry_cnt > MAX_RETRY
 	 comm_state_t = COMM_ERROR
 */
