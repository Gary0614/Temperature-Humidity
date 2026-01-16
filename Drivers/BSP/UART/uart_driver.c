/*
 * uart.c
 *
 *  Created on: Dec 7, 2025
 *      Author: lll
 */

#include "uart_driver.h"

HAL_StatusTypeDef UART_ReceiveString(char *ReceiveString)
{
	HAL_StatusTypeDef status;
	status = HAL_UART_Receive(&huart1, (uint8_t *)ReceiveString , 2, HAL_MAX_DELAY);
	return status;
}

HAL_StatusTypeDef UART_SendString(char *SendString)
{
	HAL_StatusTypeDef status;
	status = HAL_UART_Transmit(&huart1, (uint8_t *)SendString , strlen(SendString), HAL_MAX_DELAY);
	return status;
}

//HAL_StatusTypeDef UART_ReceiveData(uint8_t *ReceiveData)
//{
//	return HAL_UART_Receive(&huart1, ReceiveData , sizeof(ReceiveData), HAL_MAX_DELAY);
//}
//
//HAL_StatusTypeDef UART_SendData(uint8_t *SendData)
//{
//	return HAL_UART_Receive(&huart1, SendData , sizeof(SendData), HAL_MAX_DELAY);
//}
//
