#include "main.h"
#include "BMM150_conf.h"


#ifndef __BMM150_H
#define __BMM150_H

#define BMM150_ADR        (0x13 << 1)
#define BMM150_ERR         0



struct BMM150Commands
{
	uint8_t DEVID;	           //0x40//Номер ID
	uint8_t	DATAX_LSB;         //0x42//LSB данных о магнитном поле по оси X
	uint8_t	DATAX_MSB;	       //0x43//MSB данных о магнитном поле по оси X
	uint8_t	DATAY_LSB;         //0x44//LSB данных о магнитном поле по оси Y
	uint8_t	DATAY_MSB;	       //0x45//MSB данных о магнитном поле по оси Y
	uint8_t	DATAZ_LSB;         //0x46//LSB данных о магнитном поле по оси Z
	uint8_t	DATAZ_MSB;	       //0x47//MSB данных о магнитном поле по оси Z
	uint8_t	RHALL_LSB;	       //0x48//LSB сопротивления Холла и бит состояния готовности к передаче данных (DRDY)
	uint8_t	RHALL_MSB;	       //0x49//MSB сопротивления Холла 
	uint8_t	INT;	             //0x4A//Cостояния всех прерываний
	uint8_t	POWER_CONTROL;     //0x4B//Cодержит управляющие биты для управления питанием, плавного сброса и выбора режима интерфейса SPI
	uint8_t	OPERATION_MODE;	   //0x4C//Cодержит управляющие биты для режима работы, скорости передачи выходных данных и самопроверки.
	uint8_t	INT_AXIS_EN;	     //0x4D//Cодержит управляющие биты для настроек прерывания
	uint8_t	INT_SET_AXIS_EN;   //0x4E//Содержит управляющие биты настроек прерывания и биты включения осей
	uint8_t	LOW_THRESHOLD;     //0x4F//Содержит настройку порога прерывания с низким порогом
	uint8_t	HIGH_THRESHOLD;	   //0x50//Содержит настройку порога прерывания с высоким порогом
	uint8_t	REP_XY_AXIS;	     //0x51//Содержит количество повторений для оси X/Y
	uint8_t	REP_Z_AXIS;	       //0x52//Содержит количество повторений для оси Z
};

extern struct BMM150_Data
{
	uint8_t id  ;       // id устройства
	int16_t x, y;
	int16_t z;
	int16_t r_hall;
	//float xg, yg, zg; // единицы ускорения по X, Y, Z 
	uint8_t raw[8];
	uint8_t activity;
	uint8_t int_src;
	uint8_t status;
}__attribute__((packed)) BMM150;




int BMM150_Init(void);
void SendCommand(uint8_t, uint8_t);
void I2C_Read(uint8_t, uint8_t*, uint8_t);
void Read_Trim_Registers(void);
void Read_Mag_Data(void);

int16_t Compensate(int16_t, uint16_t);
static int16_t compensate_x(int16_t, uint16_t);
extern I2C_HandleTypeDef hi2c1;


//
#endif