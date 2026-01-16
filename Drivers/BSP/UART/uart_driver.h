/*
 * uart.h
 *
 *  Created on: Dec 7, 2025
 *      Author: lll
 */

#ifndef BSP_UART_UART_DRIVER_H_
#define BSP_UART_UART_DRIVER_H_
#include "usart.h"
#include "string.h"


HAL_StatusTypeDef UART_ReceiveString(char *ReceiveString);
HAL_StatusTypeDef UART_SendString(char *SendString);

#endif /* BSP_UART_UART_DRIVER_H_ */
