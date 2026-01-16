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
}SHT31_t;

void SHT31_Init(SHT31_t *dev, I2C_HandleTypeDef *hi2c, SHT31_PeriodicData_t	PeriodicData);


void SHT31_Task(SHT31_t *dev);

#endif /* INC_SHT31_H_ */

