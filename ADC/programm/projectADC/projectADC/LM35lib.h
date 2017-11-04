/*
 * LM35lib.h
 *
 * Created: 01.11.2017 15:46:45
 *  Author: Dante_L_Levi
 */ 


#ifndef LM35LIB_H_
#define LM35LIB_H_

#include "Main.h"
#include "ADClib.h"
#include <stdlib.h>
#include <stdio.h>

#define LOW_LEVEL_HUMIDITY 0		//���� ���������� ������� ���������
#define MIDLLE_LEVEL_HUMIDITY 1		//���� ���������� ������� ���������
#define HIGH_LEVEL_HUMIDITY 2		//���� ���������� ������� ���������


float Tempratelm35(unsigned char channel);	//������� ��������� ����������� � ������� LM35

unsigned char Val_humidity_sensor(unsigned char channel); //������� ��������� ������ ���������

float  Get_Gause_SS495a(unsigned char channel);	//������� ��������� �������� ���������� ���� � �������

#endif /* LM35LIB_H_ */