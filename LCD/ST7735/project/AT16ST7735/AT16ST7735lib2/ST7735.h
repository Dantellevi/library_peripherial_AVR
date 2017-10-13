/*
 * ST7735.h
 *
 * Created: 11.10.2017 14:43:32
 *  Author: Dante_L_Levi
 */ 


#ifndef ST7735_H_
#define ST7735_H_

#include "Main.h"
#include <stdlib.h>
#include <stdio.h>
#include "Font.h"
#include <avr/pgmspace.h>

//======================================================
#define DDR_LCD DDRD
#define PORT_LCD PORTD

#define DDRLightReg_LCD DDRB
#define PORTLightReg_LCD PORTB

#define BL 3
#define RST 7
#define CS 2   //=CE
#define RS 3   //=DC
#define MOSI 4
#define SCK 5


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208
//======================================================================
//======================================================
 
//============================Прототипы функций==========================
void write_byte(unsigned char c,unsigned char com);
void Reset();
void TFTInit();
void WriteTwoByte(unsigned char LCD_DataH,unsigned char LCD_DataL);
void TFTSingleColor(unsigned int color);
void WriteChar8x11(unsigned char x0, unsigned char y0, unsigned char s, unsigned int color);
void WriteChar5x7(unsigned char x0,unsigned char y0,unsigned char s,unsigned int color);
void WriteString8x11(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color);
void WriteString5x7(unsigned char x0,unsigned char y0,unsigned char *s,unsigned int color);
void DrawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color);
void DrawRectangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color, unsigned char fill);
void DrawCircle(unsigned char x0, unsigned char y0, unsigned char R, unsigned int color, unsigned char fill);
void DrawTriangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned int color, unsigned char fill);
void BacklightInit();

#endif /* ST7735_H_ */