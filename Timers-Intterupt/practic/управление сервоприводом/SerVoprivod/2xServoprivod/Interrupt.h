/*
 * Interrupt.h
 *
 * Created: 21.11.2017 15:10:14
 *  Author: Dante_L_Levi
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#include "Main.h"
//#include "InitilizeTimer.h"
#include <avr/interrupt.h>


#define FLAG_INT0 0
#define FLAG_INT1 1


#define FLAG_FALLING_EDGE 0		//�� ���������� ������
#define FLAG_LOW_LEVEL 1		//�� ������� ������
#define FLAG_ANY_LEVEL 2		//�� ������ �������� �������
#define FLAG_RISING_EDGE 3		//�� ������������� ������

void Initilizer_Interrupt(char flagInter,char flagcontrol);		//������� ������������� ����������




#endif /* INTERRUPT_H_ */