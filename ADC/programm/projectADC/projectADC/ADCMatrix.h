#ifndef ADCMATRIX_H_
#define ADCMATRIX_H_


#include "Main.h"
#include "ADClib.h"
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

#define SIZE_PASSWORD 3		//������ ��������� ������

#define FLAG_OK	1			//����  �������� ��������
#define FLAG_ERROR	0		//���� ������ ����� ������

 uint8_t GetValueKey_Board(unsigned char channel);	//������ ��������� ������� � ��� ����������
 uint8_t password_confird(unsigned char channel);	//������ �������� ��������� ������

#endif /* ADCMATRIX_H_ */