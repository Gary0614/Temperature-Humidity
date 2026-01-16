/*
 * myuart.h
 *
 *  Created on: Dec 15, 2025
 *      Author: lll
 */

#ifndef INC_MYUART_H_
#define INC_MYUART_H_

#include "LED.h"
#include "usart.h"
#include "string.h"
void Uart1_ReceiveToIdle ();
void Uart_Task(void);
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
#endif /* INC_MYUART_H_ */
