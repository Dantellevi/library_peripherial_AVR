/*
 * I2C.h
 *
 * Created: 31.01.2018 15:25:38
 *  Author: Dante_L_Levi
 */ 


#ifndef I2C_H_
#define I2C_H_


#include "Main.h"


void I2C_Init (void); //инициализация i2c
void I2C_StartCondition(void); //Отправим условие START
void I2C_StopCondition(void); //Отправим условие STOP
void I2C_SendByte(unsigned char c); //передача байта в шину
void I2C_SendByteByADDR(unsigned char c,unsigned char addr); //передача байта в шину на устройство по адресу
unsigned char I2C_ReadByte(void); //читаем байт
unsigned char I2C_ReadLastByte(void); //читаем последний байт


#endif /* I2C_H_ */