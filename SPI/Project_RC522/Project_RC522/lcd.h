
#ifndef LCD_H_
#define LCD_H_

#include "Main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define DDR_RS	DDRD	// ���� �� ������� ����� RS
#define DDR_E	DDRD	// ���� �� ������� ����� �
#define DDR_RW  DDRD
#define DDR_D4	DDRD	// ���� �� ������� ����� D4
#define DDR_D5	DDRD	// ���� �� ������� ����� D5
#define DDR_D6	DDRD	// ���� �� ������� ����� D6
#define DDR_D7	DDRD	// ���� �� ������� ����� D7

#define PORT_RS	PORTD	// ���� �� ������� ����� RS
#define PORT_E	PORTD	// ���� �� ������� ����� �
#define PORT_D4	PORTD	// ���� �� ������� ����� D4
#define PORT_D5	PORTD	// ���� �� ������� ����� D5
#define PORT_D6	PORTD	// ���� �� ������� ����� D6
#define PORT_D7	PORTD	// ���� �� ������� ����� D7

#define RS		0		// ����� ���� RS
#define RW		1		// ����� ���� RS
#define E		2		// ����� ���� �
#define D4		4		// ����� ���� D4
#define D5		5		// ����� ���� D5
#define D6		6		// ����� ���� D6
#define D7		7		// ����� ���� D7



#define E_SET()		(PORT_E |= (1 << E))		// � � �������
#define E_RESET()	(PORT_E &= ~(1 << E))		// � � ����
#define RS_COM()	(PORT_RS &= ~(1 << RS))		// ������ �������
#define RS_DATA()	(PORT_RS |= (1 << RS))		// ������ ������


void lcd_gotoxy(char x, char y);
void lcd_str_out(char *str);
void lcd_char_out(char data);
void lcd_init(char lcd);
void lcd_com(char com);
void lcd_out(char data);
void lcd_printStringXY(char *str,char x,char y);
void lcd_clear(void);
void lcd_simbol(char simbol, char *str);
void lcd_fsimbol(char simbol, char add, char ves);
void lcd_rus_out(char *str, char x, char y);
void LCD_PrintLongStrring(char str1[]);


#endif /* LCD_H_ */