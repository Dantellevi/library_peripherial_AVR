
#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>


#define PASSWORD_OK 1
#define PASSWORD_ERROR 2



/*
		������������ �� ������:
		PC4,PC5,PC6-�������
		PC0,PC1,PC2,PC3-������

*/

unsigned char GetMatrixValue(void);		//������� ��������� �������� � ��������� ����������
void Password_Print_Confim(void);		//�������� ������ � ����� �������������

#endif /* MATRIXKEYBOARD_H_ */