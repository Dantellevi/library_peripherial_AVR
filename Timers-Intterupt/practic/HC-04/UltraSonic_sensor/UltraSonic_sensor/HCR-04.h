/*
 * HCR_04.h
 *
 * Created: 11.12.2017 12:34:16
 *  Author: Dante_L_Levi
 */ 


#ifndef HCR_04_H_
#define HCR_04_H_

#include "Main.h"


//����������� ����� Echo
#define Echo_PORT PORTD
#define Echo_DDR DDRD
#define Echo_PIN PIND
#define EchoNPin PD2


//����������� ����� Trig
#define Trig_PORT PORTD
#define Trig_DDR  DDRD
#define Trig_PIN  PIND
#define Trig_NPin PD0

//������������ ���������� ��� �������
#define  FLAG_INT0 0
#define  FLAG_INT1 1


#define flag_start 1
#define flag_stop 0



void HC_SRC04_Init(void);	//������������� ��������������� ������� ����������
void HC_SRC04_Strop(void);	//������ �������(������������ ������)
void Init_Interruot_HC04(unsigned char flag);	//�������������  ����������
unsigned int Convert_CM( int N_t);	//������� ����������� ������� �� �������� � ��
unsigned int GetValueHSR04(void);			//��������� �������� 
void timer_Start_Stop(char flag);//������ � ��������� �������(������� ������)



#endif /* HCR_04_H_ */