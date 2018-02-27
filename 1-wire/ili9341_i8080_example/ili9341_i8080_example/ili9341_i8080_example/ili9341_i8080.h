#ifndef _ILI9341_H_
#define _ILI9341_H_

#define F_CPU 8000000UL

#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdlib.h>

#define MIN_X	0
#define MIN_Y	0

#define FONT_X 8
#define FONT_Y 8

#define DATA_DDR_0 DDRA
#define DATA_DDR_8 DDRD

#define DATA_PORT_0 PORTA
#define DATA_PORT_8 PORTD

#define COMMAND_PORT PORTB
#define COMMAND_PORT1 PORTC

#define COMMAND_DDR DDRB
#define COMMAND_DDR1 DDRC

#define LCD_DC 0   //RS(comm - 0; data - 1)
#define LCD_RES 1  //(active - 0)
#define LCD_RD 2	//(read_active - 0)
#define LCD_CS 3  //(chip_select_active - 0)
#define LCD_WR 0	//(write_active - 0)


//Basic Colors
#define CYAN	  0x07FF
#define MAGNETA   0xF81F
#define RED		0xf800
#define GREEN	0x07e0
#define BLUE	0x001f
#define BLACK	0x0000
#define YELLOW	0xffe0
#define WHITE	0xffff


extern uint16_t MAX_X, MAX_Y;
extern const unsigned char simbols[][8] PROGMEM;

uint8_t TFT_Read_Data(void);
void TFT_Send_Cmd(uint8_t cmd);
void TFT_Write_Data(uint8_t data);
void TFT_Write_Data16(uint16_t data);
void TFT_Read_Id(void);

void Init_ILI9341(uint8_t orient);
void TFT_Set_Column(uint16_t start_column,uint16_t end_colunm);
void TFT_Set_Page(uint16_t start_page,uint16_t end_page);
void TFT_Set_XY(uint16_t x, uint16_t y);
void TFT_Draw_Pixel(uint16_t x, uint16_t y,uint16_t color);

void TFT_Fill_Screen(uint16_t x_left, uint16_t x_right, uint16_t y_up, uint16_t y_down, uint16_t color);
void TFT_Fill_Rectangle(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t color);
void TFT_Draw_Char(uint16_t x, uint16_t y, uint16_t color, uint16_t phone, uint8_t ascii, uint8_t size);
void TFT_Draw_String(uint16_t x, uint16_t y, uint16_t color,uint16_t phone,const char *string, uint8_t size);

#endif 

