#include "GPS.h"
#include "HMC5883L.h"

#ifndef __MAGNETIC_H
#define __MAGNETIC_H

#define OK    0x01
#define ERROR 0x00

#define BUFFER_SIZE 128

extern Vector v; 
HMC5883L_STATUS  hmc5883l_status;

char buffer[BUFFER_SIZE];

void Send_UART(char *string) // заменить
{
	uint8_t len = strlen (string);
	HAL_UART_Transmit(&huart1, (uint8_t *) string, len, HAL_MAX_DELAY);  // transmit in blocking mode
}

void Magnetic_Init()
{
	//HMC5883L Init
	HMC5883L_Enabled();
	HMC5883L_setRange(HMC5883L_RANGE_0_88GA);
	HMC5883L_setMeasurementMode(HMC5883L_CONTINOUS);
	HMC5883L_setDataRate(HMC5883L_DATARATE_75HZ);
	HMC5883L_setSamples(HMC5883L_SAMPLES_8);
	HMC5883L_setOffset(10.68f, 22.875f);
	//GPS Init
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
  GetData();
}

void  HMC5883L_Get_Status()
{
	hmc5883l_status.DataRate = HMC5883L_getRange();
	hmc5883l_status.MeasurementMode = HMC5883L_getMeasurementMode();
	hmc5883l_status.Range = HMC5883L_getDataRate();
	hmc5883l_status.Samples = HMC5883L_getSamples();
	hmc5883l_status.read_reg[0] = HMC5883L_readRegister16(HMC5883L_REG_IDENT_A);
	hmc5883l_status.read_reg[1] = HMC5883L_readRegister16(HMC5883L_REG_IDENT_B);
	hmc5883l_status.read_reg[2] = HMC5883L_readRegister16(HMC5883L_REG_IDENT_C);
}


int GPS_SYNCING()
{
	uint8_t counter = 0;
	
	if(GPS.GPGGA.Latitude==0){
		counter++;
		Send_UART("latitude not received");
	}	
	if(GPS.GPGGA.Longitude==0){
		counter++;
		Send_UART("Longitude not received");
	}
	if(GPS.GPGGA.MSL_Altitude==0){
	  counter++;
		Send_UART("Altitude not received");
  }
	if(counter == 0){
				Send_UART("GPS is working successfully");
		    return OK;
	}else{
				Send_UART("GPS syncs");
		    return ERROR;
	}		
}

void Data_Package()
{
  GPS_Process();
	while(GPS_SYNCING() != OK){} // ждём пока GPS синхронизируется, и будет получать широту и долготу
		sprintf (buffer, "$%2hhd%2hhd%f%c%f%c%f%f%f%f",&GPS.GPGGA.UTC_Hour,     &GPS.GPGGA.UTC_Min,
																										&GPS.GPGGA.Latitude,     &GPS.GPGGA.NS_Indicator,
																										&GPS.GPGGA.Longitude,    &GPS.GPGGA.EW_Indicator,
																										&GPS.GPGGA.MSL_Altitude, &v.XAxis,
		                                                &v.YAxis,                &v.ZAxis);
//  	fresult = f_open(&fil, "file2.txt", FA_CREATE_ALWAYS | FA_WRITE);
//  	/* Writing text */
//  	strcpy (buffer, "This is File2.txt, written using ...f_write... and it says Hello from TokaevAS\n\t\t\t\t\t\t\t\t");
//  	fresult = f_write(&fil, buffer, bufsize(buffer), &bw);
//  	send_uart ("File2.txt created and data is written\n\t\t\t\t\t\t\t\t");
//  	/* Close file */
//  	f_close(&fil);
}


#endif