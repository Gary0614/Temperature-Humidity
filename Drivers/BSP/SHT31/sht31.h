/*
 * sht31.h
 *
 *  Created on: Dec 10, 2025
 *      Author: lll
 */

#ifndef INC_SHT31_H_
#define INC_SHT31_H_

#include "i2c.h"
#include "OLED.h"

typedef enum{
	SHT31_OK = 0,
	SHT31_ERROR,
	SHT31_BUSY,
}SHT31_Status_t;

typedef enum{
	SlowPeriodicDataModa = 0,
	NormalPeriodicDataModa,
	FastPeriodicDataModa,
}SHT31_PeriodicData_t;

/* SHT31 对象 */
typedef struct{
	I2C_HandleTypeDef		*hi2c;

	float					temperature;	// ℃
	float					humidity;		// %

	SHT31_PeriodicData_t	PeriodicData;

	SHT31_Status_t			status;
	uint8_t					rate;
}SHT31_t;

// 3 * 5 = 15 速率可以选择
static const uint8_t SHT31_PeriodRate[][2] = {
		{0x20, 0x2F}, {0x20, 0x24}, {0x20, 0x32},
		{0x21, 0x2D}, {0x21, 0x26}, {0x21, 0x30},
		{0x22, 0x2B}, {0x22, 0x20}, {0x22, 0x36},
		{0x23, 0x29}, {0x23, 0x22}, {0x23, 0x34},
		{0x27, 0x2A}, {0x27, 0x21}, {0x27, 0x37}
};

void SHT31_Init(SHT31_t *dev, I2C_HandleTypeDef *hi2c, SHT31_PeriodicData_t	PeriodicData);
void SHT31_Task(SHT31_t *dev);

#endif /* INC_SHT31_H_ */

