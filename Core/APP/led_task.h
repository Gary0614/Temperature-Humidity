/*
 * led_task.h
 *
 *  Created on: Dec 1, 2025
 *      Author: lll
 */

#ifndef INC_LED_TASK_H_
#define INC_LED_TASK_H_
#include "LED.h"

/* ===== LED 主模式 ===== */
typedef enum{
	LED_MODE_OFF = 0,
	LED_MODE_ON,
	LED_MODE_RUN,
	LED_MODE_ERROR
}LED_Mode_t;

/* ===== Error 子状态 ===== */
typedef enum{
	LED_ERR_OFF = 0,
	LED_ERR_ON,
	LED_ERR_PAUSE,
}LED_ErrorSubState_t;

/* ===== LED 运行上下文（核心） ===== */
typedef struct {
	/* 硬件 */
	LED_t	*led;

	/* 主状态 */
	LED_Mode_t	mode;

	/* 时间相关 */
    uint32_t last_tick;
    uint32_t period;

    /* Error 模式专用 */   //不懂
    uint8_t error_code;
    uint8_t blink_count;
    LED_ErrorSubState_t err_sub;
} LED_TaskCtx_t;



void LED_Task_Init(LED_TaskCtx_t *ctx, LED_t *led, uint32_t LED_Period);
void LED_Task_SetMode(LED_TaskCtx_t *ctx, LED_Mode_t LED_Mode);
void LED_Task_SetError(LED_TaskCtx_t *ctx, uint8_t code);
void LED_Task_Tick(void);	//只在中断中调用
void LED_Task_Loop(LED_TaskCtx_t *ctx);	//while(1)任务中使用

#endif /* INC_LED_TASK_H_ */
