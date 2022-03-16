
#ifndef __BMM150_CONF_H
#define __BMM150_CONF_H


//0x42//0x44//0x46//LSB данных о магнитном поле по оси X или Y или Z
#define SelfTestX          0x01
#define DATA_XYZ_LSD_0     0x08
#define DATA_XYZ_LSD_1     0x10
#define DATA_XYZ_LSD_2     0x20
#define DATA_XYZ_LSD_3     0x40
#define DATA_XYZ_LSD_4     0x80

//0x43//0x45//0x47//MSB данных о магнитном поле по оси X или Y или Z
#define DATA_XYZ_MSD_5     0x01
#define DATA_XYZ_MSD_6     0x02
#define DATA_XYZ_MSD_7     0x04
#define DATA_XYZ_MSD_8     0x08
#define DATA_XYZ_MSD_9     0x10
#define DATA_XYZ_MSD_10    0x20
#define DATA_XYZ_MSD_11    0x40
#define DATA_XYZ_MSD_12    0x80

//0x48//LSB сопротивления Холла и бит состояния готовности к передаче данных (DRDY)
#define DATA_READ_STAT     0x01
#define RHALL_LSD_0        0x04
#define RHALL_LSD_1        0x08
#define RHALL_LSD_2        0x10
#define RHALL_LSD_3        0x20
#define RHALL_LSD_4        0x40
#define RHALL_LSD_5        0x80

//0x49//MSB сопротивления Холла
#define RHALL_MSD_6        0x01
#define RHALL_MSD_7        0x02
#define RHALL_MSD_8        0x04
#define RHALL_MSD_9        0x08
#define RHALL_MSD_10       0x10
#define RHALL_MSD_11       0x20
#define RHALL_MSD_12       0x40
#define RHALL_MSD_13       0x80

//0x4A//Cостояния всех прерываний
#define LOW_INT_X          0x01
#define LOW_INT_Y          0x02
#define LOW_INT_Z          0x04
#define HIGH_INT_X         0x08
#define HIGH_INT_Y         0x10
#define HIGH_INT_Z         0x20
#define OVERFLOW           0x40 //Флаг состояния переполнения
#define DATA_OVERRUN       0x80 //Флаг состояния переполнения данных

//0x4B//Cодержит управляющие биты для управления питанием, плавного сброса и выбора режима интерфейса SPI
#define POWER_CONTROL_BIT  0x01
#define RESET_BIT1         0x02
#define SPI3_EN            0x03
#define RESET_BIT7         0x80

//0x4C//Cодержит управляющие биты для режима работы, скорости передачи выходных данных и самопроверки
#define TEST               0
#define OPMODE_0           1
#define OPMODE_1           2
#define DATA_RATE_0        3
#define DATA_RATE_1        4
#define DATA_RATE_2        5
#define ADV_ST_0           6 //Расширенный контрольный бит самопроверки 0
#define ADV_ST_1           7 //Расширенный контрольный бит самопроверки 1

/*!
 * @brief This internal API writes the op_mode value in the Opmode bits
 * (bits 1 and 2) of 0x4C register.
 *
 *  op_mode    |  Power mode
 * ------------|-----------------------
 *   0x00      |   BMM150_NORMAL_MODE
 *   0x01      |   BMM150_FORCED_MODE
 *   0x03      |   BMM150_SLEEP_MODE
 *  
 *  data_rate  |   Data rate (ODR)
 * ------------|-----------------------
 *   0x00      |   BMM150_DATA_RATE_10HZ
 *   0x01      |   BMM150_DATA_RATE_02HZ
 *   0x02      |   BMM150_DATA_RATE_06HZ
 *   0x03      |   BMM150_DATA_RATE_08HZ
 *   0x04      |   BMM150_DATA_RATE_15HZ
 *   0x05      |   BMM150_DATA_RATE_20HZ
 *   0x06      |   BMM150_DATA_RATE_25HZ
 *   0x07      |   BMM150_DATA_RATE_30HZ
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
 

//0x4D//Cодержит управляющие биты для настроек прерывания
#define LOW_INT_X_EN       0x01
#define LOW_INT_Y_EN       0x02
#define LOW_INT_Z_EN       0x04
#define HIGH_INT_X_EN      0x08
#define HIGH_INT_Y_EN      0x10
#define HIGH_INT_Z_EN      0x20
#define OVERFLOW_EN        0x40 //Флаг разрешения состояния переполнения 
#define DATA_OVERRUN_EN    0x80 //Флаг разрешения состояния переполнения данных

//0x4E//Содержит управляющие биты настроек прерывания и биты включения осей
#define INT_POLARITY       0x01 //Выбор полярности ввода вывода прерывания
#define INT_LATCH          0x02 //Фиксация прерывания
#define DR_POLARITY        0x04 //Полярность контактов для передачи данных (DRDY)
#define CHANNEL_X          0x08
#define CHANNEL_Y          0x10
#define CHANNEL_Z          0x20
#define INT_PIN_EN         0x40 //Включает отображение состояния прерывания на выводе INT
#define DATA_READY_PIN_EN  0x80 //Позволяет отображать статус готовности данных на выводе DRDY

/*!
 * @brief This internal API is used to enable or disable the magnetic
 * measurement of x,y,z axes based on the value of xyz_axes_control.
 *
 * @param[in] dev        : Structure instance of bmm150_dev.
 *
 *  xyz_axes_control           | Measurement axes/channel
 *  ---------------------------|--------------------------
 *	Bit 0                      | X - Channel
 *	Bit 1                      | Y - Channel
 *	Bit 2                      | Z - Channel
 *
 * @note Setting 1 - Disables Channel measurement
 * @note Setting 0 - Enables Channel measurement
 *
 * dev->settings.xyz_axes_control | Measurement axes Enabled/disabled
 * -------------------------------|------------------------------------
 *  0x01                          | Disables X axis (Y,Z axes enabled)
 *  0x02                          | Disables Y axis (X,Z axes enabled)
 *  0x04                          | Disables Z axis (X,Y axes enabled)
 *  0x07                          | Disables all X,Y,Z axes measurement
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
 
//0x4F//Содержит настройку порога прерывания с низким порогом
#define LOW_THRESHOLD_0    0x01
#define LOW_THRESHOLD_1    0x02
#define LOW_THRESHOLD_2    0x04
#define LOW_THRESHOLD_3    0x08
#define LOW_THRESHOLD_4    0x10
#define LOW_THRESHOLD_5    0x20
#define LOW_THRESHOLD_6    0x40
#define LOW_THRESHOLD_7    0x80

//0x50//Содержит настройку порога прерывания с высоким порогом
#define HIGH_THRESHOLD_0   0x01
#define HIGH_THRESHOLD_1   0x02
#define HIGH_THRESHOLD_2   0x04
#define HIGH_THRESHOLD_3   0x08
#define HIGH_THRESHOLD_4   0x10
#define HIGH_THRESHOLD_5   0x20
#define HIGH_THRESHOLD_6   0x40
#define HIGH_THRESHOLD_7   0x80

//0x51//Содержит количество повторений для оси X/Y
#define REPXY_0            0x01
#define REPXY_1            0x02
#define REPXY_2            0x04
#define REPXY_3            0x08
#define REPXY_4            0x10
#define REPXY_5            0x20
#define REPXY_6            0x40
#define REPXY_7            0x80

//0x52//Содержит количество повторений для оси Z
#define REPZ_0             0x01
#define REPZ_1             0x02
#define REPZ_2             0x04
#define REPZ_3             0x08
#define REPZ_4             0x10
#define REPZ_5             0x20
#define REPZ_6             0x40
#define REPZ_7             0x80
///////////////////////////////

#define BMM150_DATA_X_MSK		(0xF8)
#define BMM150_DATA_X_POS		(0x03)

#define BMM150_DATA_Y_MSK		(0xF8)
#define BMM150_DATA_Y_POS		(0x03)

#define BMM150_DATA_Z_MSK		(0xFE)
#define BMM150_DATA_Z_POS		(0x01)


#define BMM150_DATA_RHALL_MSK		(0xFC)
#define BMM150_DATA_RHALL_POS		(0x02)

/**\name OVERFLOW DEFINITIONS  */

#define BMM150_XYAXES_FLIP_OVERFLOW_ADCVAL	(-4096)
#define BMM150_ZAXIS_HALL_OVERFLOW_ADCVAL	  (-16384)
#define BMM150_OVERFLOW_OUTPUT			        (-32768)
#define BMM150_NEGATIVE_SATURATION_Z        (-32767)
#define BMM150_POSITIVE_SATURATION_Z        (32767)



#define BMM150_GET_BITS(reg_data, bitname)  ((reg_data & (bitname##_MSK)) >> \
							(bitname##_POS))
							
							
///////////////////////////////
#endif