/*
 * I2C.h
 *
 * Created: 31.01.2018 15:25:38
 *  Author: Dante_L_Levi
 */ 


#ifndef I2C_H_
#define I2C_H_


#include "Main.h"


void I2C_Init (void); //������������� i2c
void I2C_StartCondition(void); //�������� ������� START
void I2C_StopCondition(void); //�������� ������� STOP
void I2C_SendByte(unsigned char c); //�������� ����� � ����
void I2C_SendByteAddR(unsigned char data,unsigned char addr); //�������� ����� � ���� �� ���������� �� ������
unsigned char I2C_ReadByte(void); //������ ����
unsigned char I2C_ReadLastByte(void); //������ ��������� ����


#endif /* I2C_H_ */