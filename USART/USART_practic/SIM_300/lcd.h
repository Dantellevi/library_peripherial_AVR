/*
 Автор:              Лепотенко Александр Сергеевич
 * Имя файла:          lcd.c
 * Тип МК:			   все типы семейства Mega и семейства Ttiny
 * Тактовая частота:   F_CPU 8000000 Гц
 * Дата:               26.09.2017 17:03:30
 * Версия ПО:          ATMEL STUDIO VERSION 7.1.0
 * FUSES:              HIGH xx, LOW xx;
 * Описание:           Урезанная библиотека для работы с LCD дисплеями базирующимися на HD44780
 контроллерах. Данная библиотека работает по 4х и 8ми битной схеме подключения
 LCD, поддерживает только вывод данных на дисплей
 */ 
 #include <inttypes.h>

 //--------------------------------------------------
 //Если необходимо использовать 8-битный режим раскоментировать строку ниже
 //#define LCD_8BIT
 //--------------------------------------------------

#ifndef LCD_H_
#define LCD_H_
//---------------------------------------
#include "Main.h"
#include <stdlib.h>
#include <stdio.h>

//---------------------------------------

//----------------порты подлюченные к дислею -----------------------
#define DPIN PINA
#define DDDR DDRA
#define DPORT PORTA
//========================================
//цифрами указываем номера выводов мк подключенные к дисплею.
//	  Пин  МК  LCD
#define DB0 0  //DD0
#define DB1 1  //DD1
#define DB2 2  //DD2
#define DB3 3  //DD3
#define DB4 4  //DD4
#define DB5 5  //DD5
#define DB6 6  //DD6
#define DB7 7  //DD7
//===========================================
//Указываем порт к которому подключены выводы дисплея E, RS, R/W.
#define CDDR  DDRA
#define CPORT PORTA
//--------------Указываем порт к которому подключены выводы управления E,RS,R/W-----------------
#define E 2			// E	 СТРОБ.
#define RS 0		// R/W   R/W=1 читаем из LCD, R/W=0 записываем в LCD.
#define RW 1		// RS	 RS=0 посылаем команду в LCD, RS=1 посылаем данные в LCD.
//---------------------------------------



//---------------------------------Пользовательские функции----------------------------------
void LCDGotoXY(uint8_t,uint8_t);			             //Устанавливаем курсор в X, Y позицию
void LCDdata(uint8_t);						             //Вывести 1 символ на дисплей.
void LCDdataXY(uint8_t,uint8_t,uint8_t);	             //Вывести 1 символ на дисплей в X, Y позицию .
void LCDsendString(char*);                             //Вывести строку на дисплей
void LCDstringXY(char*,uint8_t,uint8_t);		             //Вывести строку на дисплей в позицию x,y
void LCDstring_of_sramXY(uint8_t*,uint8_t,uint8_t);			 //Вывести строку на дисплей в позицию x,y из ОЗУ
void LCDstring_of_flashXY(const uint8_t*,uint8_t, uint8_t);//Вывести строку в позицию x,y из флеша
void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y);
void LCDinit(void);							//Инициализация LCD
void LCDblank(void);			//Сделать невидимым инфо на дисплее
void LCDnblank(void);			//Сделать видимой инфо на дисплее + отключение видимых курсоров.
void LCDclear(void);			//Очистить дисплей от инфо + курсор на позицию 0,0
void LCDcursor_bl(void);		//Включить мигающий курсор
void LCDcursor_on(void);		//Включить подчеркивающий курсор
void LCDcursor_vi(void);		//Включить оба курсора
void LCDcursorOFF(void);		//Выключить курсор (любой)
void LCDacr(void);				//Cчетчик адреса AC всегда будет смещаться на n+1
void LCDacl(void);				//Cчетчик адреса AC всегда будет смещаться на n-1
void LCDcursorl(void);			//Сместить курсор влево на 1 символ
void LCDcursorr(void);			//Сместить курсор вправо на 1 символ
void LCDcursorln(uint8_t);		//Сместить курсор влево на n символов
void LCDcursorrn(uint8_t);		//Сместить курсор вправо на n символов
void LCDscreenl(void);			//Сместить экран влево на 1 символ
void LCDscreenr(void);			//Сместить экран вправо на 1 символ
void LCDscreenln(uint8_t);		//Сместить экран влево на n символов
void LCDscreenrn(uint8_t);		//Сместить экран вправо на n символов
void LCDscreenL(void);			//С каждым новым символом экран будет смещаться влево
void LCDscreenR(void);			//С каждым новым символом экран будет смещаться вправо
void LCDresshift(void);			//Курсор в позицию 0,0 + сброс всех сдвигов, изображение остается
void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y);		//преобразование целого в вещественное число
//-------------------------------------------------------------------------------------------
void lcd_put_KirilSimvol(uint8_t v,unsigned char Kmal[]);

//------------------------------------Дополнительные настройки-------------------------------
//Двухстрочный дисплей.
#define LINE0 0x00
#define LINE1 0x40
// 4 строчный дисплей
#define LINE2 0x14
#define LINE3 0x54

#endif /* LCD_H_ */