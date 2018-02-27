
#ifndef CICLEBUFFER_H_
#define CICLEBUFFER_H_

//------------------------------------------------<������������ �����������>----------------------------
#include "Main.h"
#include "USART.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//----------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//				������ ������ ����������� ����� ������� ������!
//				0, 1, 2, 4, 8, 16, 32, 64, 128, 256
//				�� ��������� ������ ������ ����� 128 ������
//-------------------------------------------------------------------------

#define BUFFER_SIZE 128U
#define BUFFER_MASK (BUFFER_SIZE-1)
#define BUFFER_TIME 15

//-------------------------------------------------------------------------
//							��������� �������
//-------------------------------------------------------------------------

void InBuffer( char val);
char IndexNumber(void);
void ClearBuffer(void);
char OutBufferStr(char *str, char lenght);
char GetData(void);


#endif /* CICLEBUFFER_H_ */