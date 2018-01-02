/*
 �����:              ��������� ��������� ���������
 * ��� �����:          lcd.c
 * ��� ��:			   ��� ���� ��������� Mega � ��������� Ttiny
 * �������� �������:   F_CPU 8000000 ��
 * ����:               26.09.2017 17:03:30
 * ������ ��:          ATMEL STUDIO VERSION 7.1.0
 * FUSES:              HIGH xx, LOW xx;
 * ��������:           ��������� ���������� ��� ������ � LCD ��������� ������������� �� HD44780
 ������������. ������ ���������� �������� �� 4� � 8�� ������ ����� �����������
 LCD, ������������ ������ ����� ������ �� �������
 */ 
 #include <inttypes.h>

 //--------------------------------------------------
 //���� ���������� ������������ 8-������ ����� ���������������� ������ ����
 //#define LCD_8BIT
 //--------------------------------------------------

#ifndef LCD_H_
#define LCD_H_
//---------------------------------------
#include "Main.h"
#include <stdlib.h>
#include <stdio.h>

//---------------------------------------

//----------------����� ����������� � ������ -----------------------
#define DPIN PINA
#define DDDR DDRA
#define DPORT PORTA
//========================================
//������� ��������� ������ ������� �� ������������ � �������.
//	  ���  ��  LCD
#define DB0 0  //DD0
#define DB1 1  //DD1
#define DB2 2  //DD2
#define DB3 3  //DD3
#define DB4 4  //DD4
#define DB5 5  //DD5
#define DB6 6  //DD6
#define DB7 7  //DD7
//===========================================
//��������� ���� � �������� ���������� ������ ������� E, RS, R/W.
#define CDDR  DDRA
#define CPORT PORTA
//--------------��������� ���� � �������� ���������� ������ ���������� E,RS,R/W-----------------
#define E 2			// E	 �����.
#define RS 0		// R/W   R/W=1 ������ �� LCD, R/W=0 ���������� � LCD.
#define RW 1		// RS	 RS=0 �������� ������� � LCD, RS=1 �������� ������ � LCD.
//---------------------------------------



//---------------------------------���������������� �������----------------------------------
void LCDGotoXY(uint8_t,uint8_t);			             //������������� ������ � X, Y �������
void LCDdata(uint8_t);						             //������� 1 ������ �� �������.
void LCDdataXY(uint8_t,uint8_t,uint8_t);	             //������� 1 ������ �� ������� � X, Y ������� .
void LCDsendString(char*);                             //������� ������ �� �������
void LCDstringXY(char*,uint8_t,uint8_t);		             //������� ������ �� ������� � ������� x,y
void LCDstring_of_sramXY(uint8_t*,uint8_t,uint8_t);			 //������� ������ �� ������� � ������� x,y �� ���
void LCDstring_of_flashXY(const uint8_t*,uint8_t, uint8_t);//������� ������ � ������� x,y �� �����
void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y);
void LCDinit(void);							//������������� LCD
void LCDblank(void);			//������� ��������� ���� �� �������
void LCDnblank(void);			//������� ������� ���� �� ������� + ���������� ������� ��������.
void LCDclear(void);			//�������� ������� �� ���� + ������ �� ������� 0,0
void LCDcursor_bl(void);		//�������� �������� ������
void LCDcursor_on(void);		//�������� �������������� ������
void LCDcursor_vi(void);		//�������� ��� �������
void LCDcursorOFF(void);		//��������� ������ (�����)
void LCDacr(void);				//C������ ������ AC ������ ����� ��������� �� n+1
void LCDacl(void);				//C������ ������ AC ������ ����� ��������� �� n-1
void LCDcursorl(void);			//�������� ������ ����� �� 1 ������
void LCDcursorr(void);			//�������� ������ ������ �� 1 ������
void LCDcursorln(uint8_t);		//�������� ������ ����� �� n ��������
void LCDcursorrn(uint8_t);		//�������� ������ ������ �� n ��������
void LCDscreenl(void);			//�������� ����� ����� �� 1 ������
void LCDscreenr(void);			//�������� ����� ������ �� 1 ������
void LCDscreenln(uint8_t);		//�������� ����� ����� �� n ��������
void LCDscreenrn(uint8_t);		//�������� ����� ������ �� n ��������
void LCDscreenL(void);			//� ������ ����� �������� ����� ����� ��������� �����
void LCDscreenR(void);			//� ������ ����� �������� ����� ����� ��������� ������
void LCDresshift(void);			//������ � ������� 0,0 + ����� ���� �������, ����������� ��������
void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y);		//�������������� ������ � ������������ �����
//-------------------------------------------------------------------------------------------
void lcd_put_KirilSimvol(uint8_t v,unsigned char Kmal[]);

//------------------------------------�������������� ���������-------------------------------
//������������ �������.
#define LINE0 0x00
#define LINE1 0x40
// 4 �������� �������
#define LINE2 0x14
#define LINE3 0x54

#endif /* LCD_H_ */