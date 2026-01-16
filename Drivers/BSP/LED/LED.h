/*
 * LED.h
 *
 *  Created on: Dec 1, 2025
 *      Author: lll
 */

#ifndef BSP_LED_LED_H_
#define BSP_LED_LED_H_

#include "gpio.h"

typedef enum{
	LED_STATE_OFF = 0,
	LED_STATE_ON
}LED_State_t;

typedef struct{
	GPIO_TypeDef *LED_GPIO;
	uint16_t LED_Pin;
} LED_t;




void LED_On(LED_t* led_t);
void LED_Off(LED_t* led_t);
void LED_Toggle(LED_t* led_t);

#endif /* BSP_LED_LED_H_ */
