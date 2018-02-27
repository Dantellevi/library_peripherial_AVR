

#ifndef LSM6DS3_H_
#define LSM6DS3_H_

#include "Main.h"
#include "USART.h"
#include "I2C.h"

#define LD_ON PORTB|=(1<<PORTB5)
#define LD_OFF PORTB&=~(1<<PORTB5)

#define LSM6DS3_ACC_GYRO_CTRL1_XL 0X10
#define LSM6DS3_ACC_GYRO_CTRL3_C 0X12
#define LSM6DS3_ACC_GYRO_FIFO_CTRL5 0X0A
#define LSM6DS3_ACC_GYRO_CTRL9_XL 0X18
//————————————————
#define LSM6DS3_ACC_GYRO_IF_INC_DISABLED 0x00
#define LSM6DS3_ACC_GYRO_IF_INC_ENABLED 0x04
#define LSM6DS3_ACC_GYRO_IF_INC_MASK 0x04
//————————————————
#define LSM6DS3_ACC_GYRO_BDU_CONTINUOS 0x00
#define LSM6DS3_ACC_GYRO_BDU_BLOCK_UPDATE 0x40
#define LSM6DS3_ACC_GYRO_BDU_MASK 0x40
//————————————————
#define LSM6DS3_ACC_GYRO_FIFO_MODE_BYPASS 0x00
#define LSM6DS3_ACC_GYRO_FIFO_MODE_FIFO 0x01
#define LSM6DS3_ACC_GYRO_FIFO_MODE_STREAM 0x02
#define LSM6DS3_ACC_GYRO_FIFO_MODE_STF 0x03
#define LSM6DS3_ACC_GYRO_FIFO_MODE_BTS 0x04
#define LSM6DS3_ACC_GYRO_FIFO_MODE_DYN_STREAM 0x05
#define LSM6DS3_ACC_GYRO_FIFO_MODE_DYN_STREAM_2 0x06
#define LSM6DS3_ACC_GYRO_FIFO_MODE_BTF 0x07
#define LSM6DS3_ACC_GYRO_FIFO_MODE_MASK 0x07
//————————————————
#define LSM6DS3_ACC_GYRO_ODR_XL_POWER_DOWN 0x00
#define LSM6DS3_ACC_GYRO_ODR_XL_13Hz 0x10
#define LSM6DS3_ACC_GYRO_ODR_XL_26Hz 0x20
#define LSM6DS3_ACC_GYRO_ODR_XL_52Hz 0x30
#define LSM6DS3_ACC_GYRO_ODR_XL_104Hz 0x40
#define LSM6DS3_ACC_GYRO_ODR_XL_208Hz 0x50
#define LSM6DS3_ACC_GYRO_ODR_XL_416Hz 0x60
#define LSM6DS3_ACC_GYRO_ODR_XL_833Hz 0x70
#define LSM6DS3_ACC_GYRO_ODR_XL_1660Hz 0x80
#define LSM6DS3_ACC_GYRO_ODR_XL_3330Hz 0x90
#define LSM6DS3_ACC_GYRO_ODR_XL_6660Hz 0xA0
#define LSM6DS3_ACC_GYRO_ODR_XL_13330Hz 0xB0
#define LSM6DS3_ACC_GYRO_ODR_XL_MASK 0xF0
//————————————————

#define LSM6DS3_ACC_GYRO_FS_XL_2g 0x00
#define LSM6DS3_ACC_GYRO_FS_XL_16g 0x04
#define LSM6DS3_ACC_GYRO_FS_XL_4g 0x08
#define LSM6DS3_ACC_GYRO_FS_XL_8g 0x0C
#define LSM6DS3_ACC_GYRO_FS_XL_MASK 0x0C
//————————————————
#define LSM6DS3_ACC_GYRO_XEN_XL_MASK 0x08
#define LSM6DS3_ACC_GYRO_YEN_XL_MASK 0x10
#define LSM6DS3_ACC_GYRO_ZEN_XL_MASK 0x20
#define LSM6DS3_ACC_GYRO_XEN_XL_ENABLED 0x08
#define LSM6DS3_ACC_GYRO_YEN_XL_ENABLED 0x10
#define LSM6DS3_ACC_GYRO_ZEN_XL_ENABLED 0x20
//————————————————
#define LSM6DS3_ACC_GYRO_OUTX_L_XL 0X28
#define LSM6DS3_ACC_GYRO_OUTX_H_XL 0X29
#define LSM6DS3_ACC_GYRO_OUTY_L_XL 0X2A
#define LSM6DS3_ACC_GYRO_OUTY_H_XL 0X2B
#define LSM6DS3_ACC_GYRO_OUTZ_L_XL 0X2C
#define LSM6DS3_ACC_GYRO_OUTZ_H_XL 0X2D
//————————————————





/*
=================================Ôóíêöèÿ ñ÷èòûâàíèÿ äàííûõ â áóôôåð ============================
*/
void I2Cx_ReadData(unsigned char Addr,unsigned char Reg,unsigned char size, unsigned char *value);



/*
================================Ñ÷èòûâàíèå Èíäèôèêàòîðà==============
*/
unsigned char Accel_ReadID(void);


/*
========================Ôóíêöèÿ èíèöèàëèçàöèè äàò÷èêà=========
*/
void Accel_Ini(void);



/*
==================================Ôóíêöèÿ ïåðåäà÷è äàííûõ================
*/

static void I2Cx_WriteData(unsigned char Addr,unsigned char Reg,unsigned char Value);



/*
============================Ôóíêöèÿ èíèöèàëèçàöèè ðåãèñòðîâ==================
*/

void AccRegistrInit(void);




/*
=================Ñ÷èòûâàåì ïîêàçàíèÿ ñ äàò÷èêà=============
*/
void Accel_ReadAcc(void);



#endif /* LSM6DS3_H_ */