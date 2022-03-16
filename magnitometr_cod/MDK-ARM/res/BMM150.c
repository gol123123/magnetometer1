#include "BMM150.h"



struct BMM150Commands BMM150Reg =
 {0x40, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
  0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52};

struct BMM150_Data BMM150;


uint8_t i2c_tx[2];
	
	
	
int BMM150_Init()
{
  SendCommand(BMM150Reg.POWER_CONTROL, POWER_CONTROL_BIT);
	
	
	
	HAL_I2C_Master_Transmit(&hi2c1, BMM150_ADR, (uint8_t*)&BMM150Reg.DEVID, 2, 100);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(&hi2c1, BMM150_ADR, (uint8_t*)&BMM150.id, 1, 100);
  
	BMM150.status = 1;
	
	if(BMM150.id != 0x32)
  {return BMM150.status = BMM150_ERR;}
	
	SendCommand(BMM150Reg.OPERATION_MODE, ((0 << OPMODE_0)|(0 << OPMODE_1)));
	SendCommand(BMM150Reg.OPERATION_MODE, ((0 << DATA_RATE_0)|(0 << DATA_RATE_1)|(0 << DATA_RATE_2)));
	
	
}	

void I2C_Read(uint8_t address, uint8_t *buffer, uint8_t length)
{
	HAL_I2C_Master_Transmit(&hi2c1, BMM150_ADR, (uint8_t*)&address, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, BMM150_ADR, (uint8_t*)&buffer, length, 100);
}
void SendCommand(uint8_t reg,uint8_t data)
{
  i2c_tx[0] = reg;
  i2c_tx[1] = data;
  HAL_I2C_Master_Transmit(&hi2c1, BMM150_ADR, (uint8_t*)i2c_tx, 2, 1000);
}



void Read_Mag_Data()
{
	HAL_I2C_Master_Transmit(&hi2c1, BMM150_ADR, (uint8_t*)&BMM150Reg.DATAX_LSB, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, BMM150_ADR, (uint8_t*)&BMM150.raw, 8, 100);
	
	BMM150.raw[0] = BMM150_GET_BITS(BMM150.raw[0], BMM150_DATA_X)- 8191;
	BMM150.raw[2] = BMM150_GET_BITS(BMM150.raw[2], BMM150_DATA_Y);
	BMM150.raw[4] = BMM150_GET_BITS(BMM150.raw[4], BMM150_DATA_Z);
	BMM150.raw[6] = BMM150_GET_BITS(BMM150.raw[6], BMM150_DATA_RHALL);
	
	BMM150.x = ((int16_t)(BMM150.raw[1] << 5) | BMM150.raw[0]);
	BMM150.y = ((int16_t)(BMM150.raw[3] << 5) | BMM150.raw[2]);
	BMM150.z = ((int16_t)(BMM150.raw[5] << 7) | BMM150.raw[4]);
	
	BMM150.r_hall = ((int16_t)(BMM150.raw[7] << 6) | BMM150.raw[6]);
	
	
  if(BMM150.x > 4096)
	{
		BMM150.x = BMM150.x - 8191; 
	}
	
	if(BMM150.y > 4096)
	{
		BMM150.y = BMM150.y - 8191; 
		
	}
	if(BMM150.z > 16384)
	{
		BMM150.z = BMM150.z - 32767;
    if(BMM150.z < (-13740))
		{
		  BMM150.z = (-16383);
		}
	}
	
	
}




