
#include "HMC5883.h"
//#include <math.h>

float mgPerDigit;

int i = 0;
Vector v;
struct HMC5883L_Data HMC5883L;
struct HMC5883LCommands HMC5883LReg =
 {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
	0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C};
 
int xOffset, yOffset;
uint8_t i2c_tx[2];
	
extern I2C_HandleTypeDef hi2c1;

Vector HMC5883L_readRaw(void)
{
    v.XAxis = HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_X_M) - xOffset;
    v.YAxis = HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_Y_M) - yOffset;
    v.ZAxis = HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_Z_L);

    return v;
}

Vector HMC5883L_readNormalize(void)
{
    v.XAxis = ((float)HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_X_M) - xOffset) * mgPerDigit;
    v.YAxis = ((float)HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_Y_M) - yOffset) * mgPerDigit;
    v.ZAxis = (float)HMC5883L_readRegister16(HMC5883LReg.HMC5883L_REG_OUT_Z_M) * mgPerDigit;

    return v;
}

void HMC5883L_setOffset(int xo, int yo)
{
    xOffset = xo;
    yOffset = yo;
}

void HMC5883L_setRange(uint8_t range)
{
    switch(range)
    {
	case HMC5883L_RANGE_0_88GA:
	    mgPerDigit = 0.73f;
	    break;

	case HMC5883L_RANGE_1_3GA:
	    mgPerDigit = 0.92f;
	    break;

	case HMC5883L_RANGE_1_9GA:
	    mgPerDigit = 1.22f;
	    break;

	case HMC5883L_RANGE_2_5GA:
	    mgPerDigit = 1.52f;
	    break;

	case HMC5883L_RANGE_4GA:
	    mgPerDigit = 2.27f;
	    break;

	case HMC5883L_RANGE_4_7GA:
	    mgPerDigit = 2.56f;
	    break;

	case HMC5883L_RANGE_5_6GA:
	    mgPerDigit = 3.03f;
	    break;

	case HMC5883L_RANGE_8_1GA:
	    mgPerDigit = 4.35f;
	    break;

	default:
	    break;
    }

    HMC5883L_writeRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_B, range);
}

void HMC5883L_setMeasurementMode(uint8_t mode)
{
	  HMC5883L_writeRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_A, NORMAL_MEASUREMENT);
    HMC5883L_writeRegister8(HMC5883LReg.HMC5883L_REG_MODE, mode);
}


void HMC5883L_setDataRate(uint8_t dataRate)
{
    HMC5883L_writeRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_A, dataRate);
}

void HMC5883L_setSamples(uint8_t samples)
{
    HMC5883L_writeRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_A, samples);
}


void HMC5883L_ID()
{
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_IDENT_A, 1, 100);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&v.id, 1, 100);
}

/*
//void HMC5883L_getRange(void)
//{
//    return (hmc5883l_range_t)((HMC5883L_readRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_B) >> 5));
//}
//
//hmc5883l_mode_t HMC5883L_getMeasurementMode(void)
//{
//    uint8_t value;

//    value = HMC5883L_readRegister8(HMC5883LReg.HMC5883L_REG_MODE);
//    value &= 0x03;

//    return (hmc5883l_mode_t)value;
//}
//
//hmc5883l_dataRate_t HMC5883L_getDataRate(void)
//{
//    uint8_t value;

//    value = HMC5883L_readRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_A);
//    value &= 0x1C;
//    value >>= 2;

//    return (hmc5883l_dataRate_t)value;
//}
//
//hmc5883l_samples_t HMC5883L_getSamples(void)
//{
//	
//    uint8_t value;

//    value = HMC5883L_readRegister8(HMC5883LReg.HMC5883L_REG_CONFIG_A);
//    value &= 0x60;
//    value >>= 5;

//    return (hmc5883l_samples_t)value;
//}
*/

// Write byte to register
void HMC5883L_writeRegister8(uint8_t reg, uint8_t value)
{
    HAL_I2C_Mem_Write(&hi2c1, HMC5883L_ADDRESS, reg, 1 , &value,1,500);
}

// Read byte to register
uint8_t HMC5883L_fastRegister8(uint8_t reg)
{
    uint8_t value;
//  HAL_I2C_Mem_Write(&I2C, HMC5883L_ADDRESS, reg, 1 ,value,1,500)
    HAL_I2C_Mem_Read(&hi2c1, HMC5883L_ADDRESS , reg, 1, &value, 1, 500);
    return value;
}

// Read byte from register
uint8_t HMC5883L_readRegister8(uint8_t reg)
{
    uint8_t value;
    HAL_I2C_Mem_Read(&hi2c1, HMC5883L_ADDRESS , reg, 1, &value, 1, 500);
    return value;
}

// Read word from register
int16_t HMC5883L_readRegister16(uint8_t reg)
{
    int16_t value;
	  
	  uint8_t vha[2];
//	
	  HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&reg, 1, 100);
	  HAL_Delay(10);
	  HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&vha, 2, 100);
	
//    HAL_I2C_Mem_Read(&hi2c1,  HMC5883L_ADDRESS, reg, 1, vha, 2, 500);
	  
	  value = ((int16_t)(vha[0] <<8) | vha[1]);
    return value;
}





int HMC5883L_init()
{
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_IDENT_A, 1, 100);
	HAL_Delay(10);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.id, 1, 100);
	
	//SendCommand(HMC5883LReg.HMC5883L_REG_CONFIG_A, HMC5883L_SAMPLES_1);
	SendCommand(HMC5883LReg.HMC5883L_REG_CONFIG_A, HMC5883L_DATARATE_3HZ);
	SendCommand(HMC5883LReg.HMC5883L_REG_CONFIG_A, NORMAL_MEASUREMENT );
	HMC5883L_setRange(HMC5883L_RANGE_0_88GA);
	SendCommand(HMC5883LReg.HMC5883L_REG_MODE, HMC5883L_CONTINOUS);

}




void SendCommand(uint8_t reg,uint8_t data)
{
  i2c_tx[0] = reg;
  i2c_tx[1] = data;
  HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)i2c_tx, 2, 1000);
}

void STATUSCommand()
{
	i++;
  SendCommand(HMC5883LReg.HMC5883L_REG_STATUS, (1));
	if(i>3)
	{i = 0;}
}

void Read_Data()
{
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_X_L, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[0], 6, 100);
	
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_X_M, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[1], 6, 100);
		
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_Y_L, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[2], 6, 100);
		
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_Y_M, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[3], 6, 100);
		
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_Z_L, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[4], 6, 100);
		
	HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883LReg.HMC5883L_REG_OUT_Z_M, 1, 100);
	HAL_Delay(100);
	HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, (uint8_t*)&HMC5883L.raw[5], 6, 100);
		
	
	HMC5883L.x = ((int16_t)(HMC5883L.raw[1] << 8) | HMC5883L.raw[0]);
	HMC5883L.y = ((int16_t)(HMC5883L.raw[3] << 8) | HMC5883L.raw[2]);
	HMC5883L.z = ((int16_t)(HMC5883L.raw[5] << 8) | HMC5883L.raw[4]);
	HAL_Delay(50);

}