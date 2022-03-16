#ifndef HMC5883L_conf_h
#define HMC5883L_conf_h


//#define HMC5883L_ADDRESS              (0x1E)
//#define HMC5883L_REG_CONFIG_A         (0x00)
//#define HMC5883L_REG_CONFIG_B         (0x01)
//#define HMC5883L_REG_MODE             (0x02)
//#define HMC5883L_REG_OUT_X_M          (0x03)
//#define HMC5883L_REG_OUT_X_L          (0x04)
//#define HMC5883L_REG_OUT_Z_M          (0x05)
//#define HMC5883L_REG_OUT_Z_L          (0x06)
//#define HMC5883L_REG_OUT_Y_M          (0x07)
//#define HMC5883L_REG_OUT_Y_L          (0x08)
//#define HMC5883L_REG_STATUS           (0x09)
//#define HMC5883L_REG_IDENT_A          (0x0A)
//#define HMC5883L_REG_IDENT_B          (0x0B)
//#define HMC5883L_REG_IDENT_C          (0x0C)
// REG_CONFIG_A
// Select number of samples averaged
#define HMC5883L_SAMPLES_1               0x00
#define HMC5883L_SAMPLES_2               0x01 
#define HMC5883L_SAMPLES_4               0x02
#define HMC5883L_SAMPLES_8               0x03

//Data Output Rate Bits
#define HMC5883L_DATARATE_0_75_HZ        ((0 << 2)|(0 << 3)|(0 << 4))  //0 << 2
#define HMC5883L_DATARATE_1_5HZ          ((1 << 2)|(0 << 3)|(0 << 4))  //1 << 2 
#define HMC5883L_DATARATE_3HZ            ((0 << 2)|(1 << 3)|(0 << 4))  //2 << 2
#define HMC5883L_DATARATE_7_5HZ          ((1 << 2)|(1 << 3)|(0 << 4))  //3 << 2
#define HMC5883L_DATARATE_15HZ           ((0 << 2)|(0 << 3)|(1 << 4))  //4 << 2
#define HMC5883L_DATARATE_30HZ           ((1 << 2)|(0 << 3)|(1 << 4))  //5 << 2
#define HMC5883L_DATARATE_75HZ           ((0 << 2)|(1 << 3)|(1 << 4))  //6 << 2

//Measurement Mode
#define NORMAL_MEASUREMENT               ((0 << 5)|(0 << 6))  //0 << 5
#define POSITIVE_BIAS_CONF               ((1 << 5)|(0 << 6))  //1 << 5 
#define NEGATIVE_BIAS_CONF               ((0 << 5)|(1 << 6))  //2 << 5

// REG_CONFIG_B
//Gain Configuration Bits
#define HMC5883L_RANGE_0_88GA            ((0 << 5)|(0 << 6)|(0 << 7))  //0 << 5
#define HMC5883L_RANGE_1_3GA             ((1 << 5)|(0 << 6)|(0 << 7))  //1 << 5 
#define HMC5883L_RANGE_1_9GA             ((0 << 5)|(1 << 6)|(0 << 7))  //2 << 5
#define HMC5883L_RANGE_2_5GA             ((1 << 5)|(1 << 6)|(0 << 7))  //3 << 5
#define HMC5883L_RANGE_4GA               ((0 << 5)|(0 << 6)|(1 << 7))  //4 << 5
#define HMC5883L_RANGE_4_7GA             ((1 << 5)|(0 << 6)|(1 << 7))  //5 << 5
#define HMC5883L_RANGE_5_6GA             ((0 << 5)|(1 << 6)|(1 << 7))  //6 << 5
#define HMC5883L_RANGE_8_1GA             ((1 << 5)|(1 << 6)|(1 << 7))  //7 << 5

//HMC5883L_REG_MODE
//Mode Select Bits.
#define HMC5883L_CONTINOUS               0x00
#define HMC5883L_SINGLE                  0x01 
#define HMC5883L_IDLE                    0x02




#endif