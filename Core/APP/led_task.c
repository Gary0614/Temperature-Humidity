/*
 * led_task.c
 *
 *  Created on: Dec 1, 2025
 *      Author: lll
 */
#include "led_task.h"

/* ===== LED Loop time ===== */
#define	LOOP_TIME	    500
#define BLINK_MAX_COUNT 20
/* ===== LED 定义（APP 层） ===== */
LED_t led_run   = { LED1_GPIO_Port, LED1_Pin };
LED_t led_error = { LED2_GPIO_Port, LED2_Pin };

/* ===== 状态机变量 ===== */
LED_TaskCtx_t LED_run_t = {
		.led = &led_run,
		.mode = LED_ERR_OFF,
		.last_tick = 0,
		.period = 500
};

/* ===== 软件定时变量 ===== */
static volatile uint32_t g_led_tick = 0;

/* ===== Init 初始化LED状态 ===== */
void LED_Task_Init(LED_TaskCtx_t *ctx, LED_t *led, uint32_t LED_Period) {
	ctx->led = led;
	ctx->mode = LED_MODE_OFF;
	ctx->last_tick = 0;
	ctx->period = LED_Period;

	ctx->error_code  = 0;
	ctx->blink_count = 0;
	ctx->err_sub     = LED_ERR_OFF;

	LED_Off(led);
}

/* ===== 模式控制 ===== */
void LED_Task_SetMode(LED_TaskCtx_t *ctx, LED_Mode_t LED_Mode){
	ctx->mode = LED_Mode;
	ctx->last_tick = g_led_tick;

	if(LED_Mode == LED_MODE_ON){
		LED_On(ctx->led);
	} else if(LED_Mode == LED_MODE_OFF){
		LED_Off(ctx->led);
	}
};

void LED_Task_SetError(LED_TaskCtx_t *ctx, uint8_t code)
{
    if (code == 0 || code > 9) return;

    ctx->error_code = code;
    LED_Task_SetMode(ctx, LED_MODE_ERROR);
}

//定时器中调用
void LED_Task_Tick(void) {
	g_led_tick++;
}

void LED_Task_Loop(LED_TaskCtx_t *ctx) {
	uint32_t now = g_led_tick;

	switch(ctx->mode)
	{
	case LED_MODE_OFF:
		LED_Off(ctx->led);
		break;
	case LED_MODE_ON:
		LED_On(ctx->led);
		break;
	case LED_MODE_RUN:
		if(now - ctx->last_tick >= ctx->period){
			ctx->last_tick = now;
			LED_Toggle(ctx->led);
		}
		break;
	case LED_MODE_ERROR:
	        /* 子状态机 */
	        switch (ctx->err_sub)
	        {
	        case LED_ERR_ON:
	            if (now - ctx->last_tick >= 200)
	            {
	                ctx->last_tick = now;
	                LED_Off(ctx->led);
	                ctx->err_sub = LED_ERR_OFF;
	            }
	            break;

	        case LED_ERR_OFF:
	            if (now - ctx->last_tick >= 200)
	            {
	                ctx->last_tick = now;
	                ctx->blink_count++;

	                if (ctx->blink_count >= ctx->error_code)
	                {
	                    ctx->err_sub = LED_ERR_PAUSE;
	                }
	                else
	                {
	                    LED_On(ctx->led);
	                    ctx->err_sub = LED_ERR_ON;
	                }
	            }
	            break;

	        case LED_ERR_PAUSE:
	            if (now - ctx->last_tick >= 1000)
	            {
	                ctx->last_tick   = now;
	                ctx->blink_count = 0;
	                LED_On(ctx->led);
	                ctx->err_sub = LED_ERR_ON;
	            }
	            break;
	        }
	        break;
	}
}
