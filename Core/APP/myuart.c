/*
 * myuart.c
 *
 *  Created on: Dec 15, 2025
 *      Author: lll
 */
#include "myuart.h"

#include "led_task.h"
#include "sht31.h"
#include "stdio.h"

#define	RX_BUF_MAX	64


extern DMA_HandleTypeDef hdma_usart1_rx;
extern LED_TaskCtx_t LED_run_t;
extern SHT31_t	SHT31_Dev_t;

uint8_t receiveData[RX_BUF_MAX];
uint16_t uart_rx_len;

volatile uint8_t uart_rx_flag = 0;

//接受不定长数据
void Uart1_ReceiveToIdle() {
	HAL_UARTEx_ReceiveToIdle_DMA(&uart1, receiveData, sizeof(receiveData));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}

static void remove_crlf(char *str) {
	char *p;
	p = strchr(str, '\r');
	if (p)
		*p = '\0';
	p = strchr(str, '\n');
	if (p)
		*p = '\0';
}

void Uart_CmdLed(char *arg){
	if(strcmp(arg, "ON") == 0){
		LED_Task_SetMode(&LED_run_t, LED_MODE_ON);
		UART_SendString("Led On Successfully\r\n");
	}else if(strcmp(arg, "OFF") == 0){
		LED_Task_SetMode(&LED_run_t, LED_MODE_OFF);
		UART_SendString("Led Off Successfully\r\n");
	}else if(strcmp(arg, "TOGGLE") == 0){
		if(LED_run_t.mode == LED_MODE_ON){
			LED_Task_SetMode(&LED_run_t, LED_MODE_OFF);
			UART_SendString("Led Toggle Successfully\r\n");
		}else if(LED_run_t.mode == LED_MODE_OFF){
			LED_Task_SetMode(&LED_run_t, LED_MODE_ON);
			UART_SendString("Led Toggle Successfully\r\n");
		}else
			UART_SendString("$ERR#");
	}
}

void Uart_CmdGetTemp(void)
{
  /*  传输温湿度数据   */
    char tx_buf[64];

    snprintf(tx_buf, sizeof(tx_buf),
             "$TEMP:%d,HUM:%d#\r\n",
			 (int)(SHT31_Dev_t.temperature * 100),
			 (int)(SHT31_Dev_t.humidity * 100));

    UART_SendString(tx_buf);
}


void Uart_CmdDispatch(char *cmd){
	if(strncmp(cmd, "LED:", 4) == 0){
		Uart_CmdLed(cmd + 4);
	}else if(strcmp(cmd, "GET:TEMP") == 0){
		Uart_CmdGetTemp();
	}else{
		UART_SendString("$ERR#");
	}
}




void command_parse(char *buf, uint16_t len) {
	remove_crlf(buf);

	buf[uart_rx_len - 1] = '\0';	/* 去掉帧尾 */

	char *payload = (char *)&buf[1];	/* 跳过 '$' */

	strtok(payload, "\r\n");	/* 去掉可能的 \r\n */

	Uart_CmdDispatch(payload);

}

void Uart_Task(void) {
	if (uart_rx_flag) {
		uart_rx_flag = 0;
	}
	if (receiveData[0] != '$' || receiveData[uart_rx_len - 1] != '#')
	        return;

	command_parse((char*) receiveData, uart_rx_len);
}

/*    -----发送数据给ESP32-----    */
void ESP32_Send_SHT31(int16_t temp_x100, int16_t humi_x100)
{
	char buf[64];
	int len = snprintf(buf, sizeof(buf), "$DATA:%d,%d\r\n", temp_x100, humi_x100);

	HAL_UART_Transmit_DMA(&uart1, (uint8_t *)buf, len);
}


/* ----- UART 回调函数-----  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
		if (huart == &uart1) {
			receiveData[Size] = '\0';  // 关键：补 \0
			uart_rx_len = Size;
			uart_rx_flag = 1; //接受标志位
			HAL_UARTEx_ReceiveToIdle_DMA(&uart1, receiveData, sizeof(receiveData));
			__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
		}
	}
