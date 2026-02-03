/*
 * sht31.c
 *
 *  Created on: Dec 10, 2025
 *      Author: lll
 */

#include "sht31.h"
#include <stdlib.h>
#define SHT31_ADDRESS	0x44
#define SHT31_I2C	    &hi2c2
#define CRC8_POLYNOMIAL 0x31


float g_Temp = 2.0;
float g_Humi = 0.0;
float set_Temp = 2.0;
float set_Humi = 0.0;

uint8_t rbuf[6];

SHT31_t	SHT31_Dev_t;



void SHT31_SendTwoCmd(uint8_t MSB, uint8_t LSB){
	uint8_t CmdData[2] = {MSB, LSB};
	HAL_I2C_Master_Transmit(SHT31_I2C, SHT31_ADDRESS << 1, CmdData, sizeof(CmdData), 0xff);
	HAL_Delay(20);
}

//void SHT31_NormalPeriodicDataModa(void){
//	uint8_t CmdData[2] = {0x21, 0x30};
//	HAL_I2C_Master_Transmit(SHT31_I2C, SHT31_ADDRESS << 1, CmdData, sizeof(CmdData), 0xff);
//}
//
//void SHT31_FastPeriodicDataModa(void){
//	uint8_t CmdData[2] = {0x27, 0x37};
//	HAL_I2C_Master_Transmit(SHT31_I2C, SHT31_ADDRESS << 1, CmdData, sizeof(CmdData), 0xff);
//}
//
//void SHT31_SlowPeriodicDataModa(void){
//	uint8_t CmdData[2] = {0x20, 0x32};
//	HAL_I2C_Master_Transmit(SHT31_I2C, SHT31_ADDRESS << 1, CmdData, sizeof(CmdData), 0xff);
//}

void SHT31_Init(SHT31_t *dev, I2C_HandleTypeDef *hi2c, SHT31_PeriodicData_t	PeriodicData){
	dev->hi2c 			= hi2c;
	dev->temperature 	= 0.0f;
	dev->humidity 		= 0.0f;
	dev->PeriodicData 	= PeriodicData;
	dev->status 		= SHT31_OK;
	dev->rate			= 7;

	SHT31_SendTwoCmd(SHT31_PeriodRate[dev->rate][0], SHT31_PeriodRate[dev->rate][1]);

	SHT31_SendTwoCmd(0xE0, 0x00);	//获取SHT31数据
}

uint8_t static CheckCrc8(uint8_t *const message, uint8_t initial_value) {
	uint8_t remainder;        //余数
	uint8_t i = 0, j = 0;  //循环变量

	/* 初始化 */
	remainder = initial_value;
	for (j = 0; j < 2; j++) {
		remainder ^= message[j];
		/* 从最高位开始依次计算  */
		for (i = 0; i < 8; i++) {
			if (remainder & 0x80) {
				remainder = (remainder << 1) ^ CRC8_POLYNOMIAL;
			} else {
				remainder = (remainder << 1);
			}
		}
	}
	/* 返回计算的CRC码 */
	return remainder;
}

uint8_t static GXHT3L_Dat_To_Float(uint8_t *const dat, float *temperature,
		float *humidity) {
	uint16_t recv_temperature = 0;
	uint16_t recv_humidity = 0;

	/* 校验温度数据和湿度数据是否接收正确 */
	if (CheckCrc8(dat, 0xFF) != dat[2] || CheckCrc8(&dat[3], 0xFF) != dat[5])
		return 1;

	/* 转换温度数据 */
	recv_temperature = ((uint16_t) dat[0] << 8) | dat[1];
	*temperature = -45 + 175 * ((float) recv_temperature / 65535);

	/* 转换湿度数据 */
	recv_humidity = ((uint16_t) dat[3] << 8) | dat[4];
	*humidity = 100 * ((float) recv_humidity / 65535);

	return 0;
}

void SHT31_Task(SHT31_t *dev){
	uint8_t rbuf[6];
		if (HAL_OK == HAL_I2C_Master_Receive(SHT31_I2C, (SHT31_ADDRESS << 1) + 1, rbuf,
		sizeof(rbuf), HAL_MAX_DELAY)) {
		if (GXHT3L_Dat_To_Float(rbuf, &dev->temperature, &dev->humidity) == 0) {
			//printf("temperature = %f, humidity = %f\n", temperature, humidity);

			OLED_ShowNum(2, 8, dev->humidity, 2);
			OLED_ShowString(2, 10, ".");
			OLED_ShowNum(2, 11, (int)(dev->humidity * 100) % 100, 2);

			OLED_ShowNum(2, 1, dev->temperature, 2);
			OLED_ShowString(2, 3, ".");
			OLED_ShowNum(2, 4, (int)(dev->temperature * 100) % 100, 2);

			OLED_ShowString(4, 1, "success!");
		} else {
			OLED_ShowString(4, 1, "          ");
			OLED_ShowString(4, 1, "CRC Wrong!");
		}
	} else {
		OLED_ShowString(4, 1, "          ");
		OLED_ShowString(4, 1, "Error");
	}

	dev->status = SHT31_OK;
}

