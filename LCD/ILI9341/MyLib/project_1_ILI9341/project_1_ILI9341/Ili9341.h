//==================<библиотека дисплея ILI9341>==========


#ifndef ILI9341_H_
#define ILI9341_H_

#include "Main.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#define swap(a,b) {int16_t t=a;a=b;b=t;}
#define DATA_DDR DDRD
#define DATA_PORT PORTD
#define DATA_PIN PIND

#define COMMAND_DDR DDRB
#define COMMAND_PORT PORTB

#define LCD_CS	4
#define LCD_CD	1
#define LCD_WR	3
#define LCD_RESET	0
#define  LCD_RD 2//LCD Read

#define  RESET_IDLE COMMAND_PORT|=(1<<LCD_RESET)
#define  CS_IDLE COMMAND_PORT|=(1<<LCD_CS)
#define  WR_IDLE COMMAND_PORT|=(1<<LCD_WR)
#define  RD_IDLE COMMAND_PORT|=(1<<LCD_RD)
#define  RESET_ACTIVE COMMAND_PORT&=~(1<<LCD_RESET)
#define  CS_ACTIVE COMMAND_PORT&=~(1<<LCD_CS)
#define  WR_ACTIVE COMMAND_PORT&=~(1<<LCD_WR)
#define  RD_ACTIVE COMMAND_PORT&=~(1<<LCD_RD)
#define  CD_COMMAND COMMAND_PORT&=~(1<<LCD_CD)
#define  CD_DATA COMMAND_PORT|=(1<<LCD_CD)

#define  BLACK 0x0000
#define  BLUE 0x001F
#define  RED 0x0F800
#define  GREEN 0x07E0
#define  CYAN 0x07FF
#define  MAGENTA 0xF81F
#define  YELLOW 0xFFE0
#define  WHITE 0xFFFF


#define   setReadDir() DATA_DDR=0x00
#define   setWriteDir() DATA_DDR=0xFF

#define  WR_STROBE {WR_ACTIVE;WR_IDLE;}


//=======================<Прототипы>===============
void Port_init(void);
void TFT9341_init(void);
void TFT9341_SendCommand(unsigned char cmd);
void TFT9341_SendData(unsigned char dt);
void TFT9341_reset(void);
void TFT9341_Write8(unsigned char data);
unsigned long TFT9341_ReadReg(unsigned char r);
void TFT9341_SetRotation(unsigned char r);
void TFT9341_Flood(unsigned short color,unsigned long len);
void TFT9341_WriteRegister32(unsigned char r, unsigned long d);
void TFT9341_SetAddrWindow(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void TFT9341_FillScreen(unsigned int color);
void TFT9341_FillRectangle(unsigned int color,unsigned int x1, unsigned int y1,unsigned int x2, unsigned int y2);
void TFT9341_DrawPixel(int x, int y, unsigned int color);
void TFT9341_DrawLine(unsigned int color,unsigned int x1, unsigned int y1,unsigned int x2, unsigned int y2);
void TFT9341_DrawRect(unsigned int color,unsigned int x1, unsigned int y1,unsigned int x2, unsigned int y2);
void TFT9341_DrawCircle(unsigned int x0, unsigned int y0, int r, unsigned int color);
unsigned int TFT9341_RandColor(void);
void TFT9341_Draw_Char(int x, int y, unsigned int color, unsigned int phone,unsigned char charcode, unsigned char size);
void TFT9341_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone,char *str, unsigned char size);







#endif /* ILI9341_H_ */