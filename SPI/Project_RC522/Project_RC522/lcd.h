
#ifndef LCD_H_
#define LCD_H_

#include "Main.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define DDR_RS	DDRD	// Порт на котором будет RS
#define DDR_E	DDRD	// Порт на котором будет Е
#define DDR_RW  DDRD
#define DDR_D4	DDRD	// Порт на котором будет D4
#define DDR_D5	DDRD	// Порт на котором будет D5
#define DDR_D6	DDRD	// Порт на котором будет D6
#define DDR_D7	DDRD	// Порт на котором будет D7

#define PORT_RS	PORTD	// Порт на котором будет RS
#define PORT_E	PORTD	// Порт на котором будет Е
#define PORT_D4	PORTD	// Порт на котором будет D4
#define PORT_D5	PORTD	// Порт на котором будет D5
#define PORT_D6	PORTD	// Порт на котором будет D6
#define PORT_D7	PORTD	// Порт на котором будет D7

#define RS		0		// Номер пина RS
#define RW		1		// Номер пина RS
#define E		2		// Номер пина Е
#define D4		4		// Номер пина D4
#define D5		5		// Номер пина D5
#define D6		6		// Номер пина D6
#define D7		7		// Номер пина D7



#define E_SET()		(PORT_E |= (1 << E))		// Е в единицу
#define E_RESET()	(PORT_E &= ~(1 << E))		// Е в ноль
#define RS_COM()	(PORT_RS &= ~(1 << RS))		// Запись команды
#define RS_DATA()	(PORT_RS |= (1 << RS))		// Запись данных


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