/*
 * LED.c
 *
 *  Created on: Dec 1, 2025
 *      Author: lll
 */

#include "LED.h"
#include "main.h"


void LED_On(LED_t* led_t)
{
	HAL_GPIO_WritePin(led_t->LED_GPIO, led_t->LED_Pin, GPIO_PIN_RESET);
}

void LED_Off(LED_t* led_t)
{
	HAL_GPIO_WritePin(led_t->LED_GPIO, led_t->LED_Pin, GPIO_PIN_SET);
}

void LED_Toggle(LED_t* led_t)
{
	HAL_GPIO_TogglePin(led_t->LED_GPIO, led_t->LED_Pin);
}

//uint8_t LED_Set(LED_t* led_t, LED_State_t state){
//	if(state == LED_OFF){
//		HAL_GPIO_WritePin(led_t->LED_GPIO, led_t->LED_Pin, GPIO_PIN_SET);
//	}
//	else if(state == LED_ON){
//		HAL_GPIO_WritePin(led_t->LED_GPIO, led_t->LED_Pin, GPIO_PIN_RESET);
//	}
//}
