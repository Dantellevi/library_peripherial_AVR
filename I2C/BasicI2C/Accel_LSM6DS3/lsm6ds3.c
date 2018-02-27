#include "lsm6ds3.h"

unsigned char read_buf[10]={0};
char str1[30]={0};

void Error(void)
{
	LD_ON;

}

/*
========================Функция инициализации датчика=========
*/
void Accel_Ini(void)
{
	
	_delay_ms(500);
	Accel_ReadID();
	if (read_buf[0]!=0x69)
	{
		Error();
	}
	AccRegistrInit();
}




/*
================================Считывание Индификатора==============
*/
unsigned char Accel_ReadID(void)
{
	unsigned char ctrl=0;
	I2Cx_ReadData(0xD4,0x0E,1,read_buf);
	return ctrl;


}


/*
=================================Функция считывания данных в буффер ============================
*/
void I2Cx_ReadData(unsigned char Addr,unsigned char Reg,unsigned char size, unsigned char *value)
{
	unsigned char i=size,n=0;
	Start_I2C();//начинаем передачу 
	I2C_SendByte(Addr);// передаем адрес
	I2C_SendByte(Reg);//передаем регистр
	Stop_I2C();// Останавливаем работу интерфейса
	I2C_SendByte(Addr|0x01);//передаем адрес устройства и бит чтения (1)


	while (1)
	{
		if (i==1)
		{
			break;
		}
		value[n]=I2C_ReadByte();
		i--;
		n++;
	}

	value[size-1]=I2C_ReadLastByte();//прочитаем последний байт
	Stop_I2C();

}


/*
==================================Функция передачи данных================
*/

static void I2Cx_WriteData(unsigned char Addr,unsigned char Reg,unsigned char Value)
{
	Start_I2C();
	I2C_SendByte(Addr);
	I2C_SendByte(Reg);
	I2C_SendByte(Value);
	Stop_I2C();

}

/*
============================Функция инициализации регистров==================
*/

void AccRegistrInit(void)
{
	//автоувеличение адреса регистра

	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL3_C,1,read_buf);
	read_buf[0]&=~LSM6DS3_ACC_GYRO_IF_INC_MASK;
	read_buf[0]|=LSM6DS3_ACC_GYRO_IF_INC_ENABLED;
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL3_C,read_buf[0]);


	//установим бит BDU(обновление данных)

	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL3_C,1,read_buf);
	read_buf[0]&=~LSM6DS3_ACC_GYRO_BDU_MASK;
	read_buf[0]|=LSM6DS3_ACC_GYRO_BDU_BLOCK_UPDATE;
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL3_C,read_buf[0]);



	//выбор режима FIFO
	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_FIFO_CTRL5,1,read_buf);
	read_buf[0]&=~LSM6DS3_ACC_GYRO_FIFO_MODE_MASK;
	read_buf[0]|=LSM6DS3_ACC_GYRO_FIFO_MODE_BYPASS;
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_FIFO_CTRL5,read_buf[0]);

	//временно откл. датчик
	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,1,read_buf);
	read_buf[0]&=~LSM6DS3_ACC_GYRO_ODR_XL_MASK;
	read_buf[0]|=LSM6DS3_ACC_GYRO_ODR_XL_POWER_DOWN;
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,read_buf[0]);

	//Full scale selection 2G(вкл. амплитуду измерений)

	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,1,read_buf);
	read_buf[0]&=~LSM6DS3_ACC_GYRO_FS_XL_MASK;
	read_buf[0]|=LSM6DS3_ACC_GYRO_FS_XL_2g;
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,read_buf[0]);



	//Включим оси
	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL9_XL,1,read_buf);
	read_buf[0]&=~
	(LSM6DS3_ACC_GYRO_XEN_XL_MASK|LSM6DS3_ACC_GYRO_YEN_XL_MASK|LSM6DS3_ACC_GYRO_ZEN_XL_MASK);

	read_buf[0]|=
	(LSM6DS3_ACC_GYRO_XEN_XL_ENABLED|LSM6DS3_ACC_GYRO_YEN_XL_ENABLED|LSM6DS3_ACC_GYRO_ZEN_XL_ENABLED);
	I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL9_XL,read_buf[0]);



	 //Включим Data Rate 104 Гц

	 I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,1,read_buf);
	 read_buf[0]&=~LSM6DS3_ACC_GYRO_ODR_XL_MASK;
     read_buf[0]|=LSM6DS3_ACC_GYRO_ODR_XL_104Hz;
	 I2Cx_WriteData(0xD4,LSM6DS3_ACC_GYRO_CTRL1_XL,read_buf[0]);




}

/*
============================Получение данных с датчика==============
*/
void Accel_GetXYZ(int16_t* pData)
{
	uint8_t buffer[6];
	uint8_t i=0;
	I2Cx_ReadData(0xD4,LSM6DS3_ACC_GYRO_OUTX_L_XL,6,buffer);
	for(i=0;i<3;i++)
	{
		pData[i] = ((int16_t)((uint16_t)buffer[2*i+1]<<8)+buffer[2*i]);
	}

}

//———————————————


/*
=================Считываем показания с датчика=============
*/
void Accel_ReadAcc(void)
{
	int16_t buffer[3] = {0};
	int16_t xval, yval, zval;
	Accel_GetXYZ(buffer);
	xval=buffer[0];
	yval=buffer[1];
	zval=buffer[2];
	sprintf(str1,"X:%06d Y:%06d Z:%06drn", xval, yval, zval);
	USART_TX((uint8_t*)str1,strlen(str1));
	_delay_ms(200);

	/*=======================для программы построения графика
	buf2[0]=0x11;

	buf2[1]=0x55;

	buf2[2]=(uint8_t)(xval>>8);

	buf2[3]=(uint8_t)xval;

	buf2[4]=(uint8_t)(yval>>8);

	buf2[5]=(uint8_t)yval;

	buf2[6]=(uint8_t)(zval>>8);

	buf2[7]=(uint8_t)zval;

	USART_TX(buf2,8);

	*/

}














