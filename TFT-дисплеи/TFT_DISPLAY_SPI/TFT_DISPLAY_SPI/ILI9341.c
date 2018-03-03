#include "Ili9341.h"
#include "Fonts.h"

unsigned int X_SIZE = 0;
unsigned int Y_SIZE = 0;

void ili9341_select_chip(void)
{
	PORTB &= ~CONF_ILI9341_CS_PIN;
}
 void ili9341_deselect_chip(void)
{
	PORTB |= CONF_ILI9341_CS_PIN;
}
 void ili9341_select_command_mode(void)
{
	PORTB &= ~CONF_ILI9341_DC_PIN;
}
void ili9341_select_data_mode(void)
{
	PORTB |= CONF_ILI9341_DC_PIN;
}
 void ili9341_send_byte(uint8_t data)
{
	//ili9341_select_chip();
	SPI_MasterTransmit(data);
}
static void ili9341_send_word(unsigned int data)
{
	SPI_MasterTransmit(data >> 8);
	SPI_MasterTransmit(data );
}
unsigned char ili9341_read_byte(void)
{
	ili9341_select_chip();
	return SPI_MasterTransmit(0);
}

void ili9341_send_command(unsigned char command)
{
	ili9341_select_command_mode();
	ili9341_select_chip();
	ili9341_send_byte(command);
	ili9341_select_data_mode();
}
void ili9341_interface_init(void)
{
	DDRB |= CONF_ILI9341_RESET_PIN | CONF_ILI9341_DC_PIN | CONF_ILI9341_CS_PIN;
	ili9341_deselect_chip();
	SPI_MasterInit();
	SPI_MasterTransmit(0);
}
void ili9341_write_buffer(char *buffer, unsigned char len)
{
	unsigned char count, data1; //, data2;
	ili9341_select_data_mode();
	ili9341_select_chip();
	for(count=0;count<len;count++)
	{
		data1 = buffer[count]; //>>8;
		//data2 = buffer[count] & 0xFF;
		SPI_MasterTransmit( data1 );
		//SPI_MasterTransmit( data2 );
	}

	//INT16U    data1 = 0;
	//    INT8U   data2 = 0;
	//    TFT_DC_HIGH;
	//    TFT_CS_LOW;
	//    INT8U count=0;
	//    for(count=0;count<howmany;count++)
	//    {
	//        data1 = data[count]>>8;
	//        data2 = data[count]&0xff;
	//        SPI.transfer(data1);
	//        SPI.transfer(data2);
	//    }
	//    TFT_CS_HIGH;

}


unsigned char ili9341_read_register(unsigned char addr, unsigned char xparam)
{
	unsigned char data;
	ili9341_send_command(0xD9); /* ext command                  */
	ili9341_send_byte(0x10+xparam); /* 0x11 is the first Parameter  */
	ili9341_select_command_mode();
	ili9341_select_chip();
	ili9341_send_byte(addr);
	ili9341_select_data_mode();
	data=ili9341_read_byte();
	ili9341_deselect_chip();
	return data;
}

//INT8U TFT::readID(void)
unsigned char ili9341_read_ID(void)
{
	unsigned char i;
	unsigned char data[3];
	unsigned char id[3]= {0x00, 0x93, 0x41};
	unsigned char ToF=0xFF;
	for(i=0;i<3;i++)
	{
		data[i]=ili9341_read_register(0xd3,i+1);
		if(data[i] != id[i])
		{
			ToF=0;
		}
	}
	Usart_PrintString("ID TFT Display:\r\n");
	Usart_char_out(data[0]);
	Usart_PrintString("-----------------------\r\n");
	Usart_char_out(data[1]);
	Usart_PrintString("-----------------------\r\n");
	Usart_char_out(data[2]);
	Usart_PrintString("-----------------------\r\n");

	return ToF;

}

void ili9341_controller_init_registers(void)
{
	 unsigned char i=0, TFTDriver=0;
	 DDRB|=(1<<PB1);
	 PORTB|=(1<<PB1);
	 for(i=0;i<3;i++)
	 {
		 TFTDriver = ili9341_read_ID();
	 }
	 _delay_ms(100);

	 ili9341_send_command(ILI9341_CMD_SOFTWARE_RESET);
	 _delay_ms(200);
	 
	 ili9341_send_command(ILI9341_CMD_SLEEP_OUT);	// Exit Sleep
	 ili9341_deselect_chip();
	 _delay_ms(220);

	 ili9341_send_command(ILI9341_CMD_POWER_CONTROL_B);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x8B); //83
	 ili9341_send_byte(0X30);

	 ili9341_send_command(0xED); //Power on sequence control
	 ili9341_send_byte(0x67); //64
	 ili9341_send_byte(0x03);
	 ili9341_send_byte(0X12);
	 ili9341_send_byte(0X81);
	 ili9341_send_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	 ili9341_send_byte(0x85);
	 ili9341_send_byte(0x10);
	 ili9341_send_byte(0x7A); //79

	 ili9341_send_command(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	 ili9341_send_byte(0x39);
	 ili9341_send_byte(0x2C);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x34);
	 ili9341_send_byte(0x02);

	 ili9341_send_command(ILI9341_CMD_PUMP_RATIO_CONTROL);
	 ili9341_send_byte(0x20);

	 ili9341_send_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x00);

	 ili9341_send_command(ILI9341_CMD_POWER_CONTROL_1 );		// Power control
	 ili9341_send_byte(0x1B); //26								// VRH[5:0]

	 ili9341_send_command(ILI9341_CMD_POWER_CONTROL_2);		// Power control
	 ili9341_send_byte(0x10); //11							// SAP[2:0];BT[3:0]

	 ili9341_send_command(ILI9341_CMD_VCOM_CONTROL_1);		// VCM control
	 ili9341_send_byte(0x3F); //35
	 ili9341_send_byte(0x3C); //3e

	 ili9341_send_command(ILI9341_CMD_VCOM_CONTROL_2);		// VCM control2
	 ili9341_send_byte(0xB7); //be

	 ili9341_send_command(ILI9341_CMD_MEMORY_ACCESS_CONTROL);	// Memory Access Control
	 ili9341_send_byte(0x08);

	 ili9341_send_command(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	 ili9341_send_byte(0x55);

	 ili9341_send_command(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x1B);

	 ili9341_send_command(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);	// Display Function Control
	 ili9341_send_byte(0x0A);
	 ili9341_send_byte(0xA2);

	 ili9341_send_command(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);	// 3Gamma Function Disable
	 ili9341_send_byte(0x00);

	 ili9341_send_command(ILI9341_CMD_GAMMA_SET); 				// Gamma curve selected
	 ili9341_send_byte(0x01);

	 ili9341_send_command(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);	// Set Gamma
	 ili9341_send_byte(0x0F);
	 ili9341_send_byte(0x2A);
	 ili9341_send_byte(0x28);
	 ili9341_send_byte(0x08);
	 ili9341_send_byte(0x0E);
	 ili9341_send_byte(0x08);
	 ili9341_send_byte(0x54);
	 ili9341_send_byte(0XA9);
	 ili9341_send_byte(0x43);
	 ili9341_send_byte(0x0A);
	 ili9341_send_byte(0x0F);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x00);

	 ili9341_send_command(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);	// Set Gamma
	 ili9341_send_byte(0x00);
	 ili9341_send_byte(0x15);
	 ili9341_send_byte(0x17);
	 ili9341_send_byte(0x07);
	 ili9341_send_byte(0x11);
	 ili9341_send_byte(0x06);
	 ili9341_send_byte(0x2B);
	 ili9341_send_byte(0x56);
	 ili9341_send_byte(0x3C);
	 ili9341_send_byte(0x05);
	 ili9341_send_byte(0x10);
	 ili9341_send_byte(0x0F);
	 ili9341_send_byte(0x3F);
	 ili9341_send_byte(0x3F);
	 ili9341_send_byte(0x0F);
}

void ili9341_reset_display(void)
{
	PORTB |= CONF_ILI9341_RESET_PIN;
	_delay_ms(20);
	PORTB &= ~CONF_ILI9341_RESET_PIN;
	_delay_ms(120);
	PORTB |= CONF_ILI9341_RESET_PIN;
	_delay_ms(250);
}
void ili9341_exit_standby(void)
{
	ili9341_send_command(ILI9341_CMD_SLEEP_OUT);
	_delay_ms(150);
	ili9341_send_command(ILI9341_CMD_DISPLAY_ON);
}
void ili9341_init(void)
{
	/* Initialize the communication interface */
	ili9341_interface_init();

	/* Harware Reset the display */
	ili9341_reset_display();

	/* Write all the controller registers with correct values */
	ili9341_controller_init_registers();
	/* Send commands to exit standby mode */
	ili9341_exit_standby();
	ili9341_deselect_chip();
	
}



void ili9341_setCol(unsigned int x0,unsigned int x1)
{
	ili9341_send_command(0x2A);                                                      /* Column Command address       */
	ili9341_send_word(x0);
	ili9341_send_word(x1);
}

void ili9341_setPage(unsigned int y0,unsigned int y1)
{
	ili9341_send_command(0x2B);                                                      /* Column Command address       */
	ili9341_send_word(y0);
	ili9341_send_word(y1);
}

void ili9341_setXY(unsigned int x, unsigned int y)
{
	ili9341_setCol(x, x);
	ili9341_setPage(y, y);
}


/* ********************** common subs ***************** */

void lcdDrawPixel(unsigned int poX, unsigned int poY, unsigned int color)
{
	ili9341_setXY(poX, poY);
	ili9341_send_command(0x2c);
	ili9341_send_word(color);
}
/* ******** same as drawpixel, but bigger ***** */
void lcdFilledRec(unsigned int x, unsigned int y, unsigned int w, unsigned int h,unsigned int color)
{
	unsigned long i;
	unsigned long n=(unsigned long) w*h;
	unsigned int x1=x+w-1;
	unsigned int y1=y+h-1;

	ili9341_setCol( x, x1);
	ili9341_setPage(y, y1);
	ili9341_send_command(0x2c);
	for(i=0;i<n;i++) { ili9341_send_word(color); }
}
/* ********** Clear screen ************ */
void lcdFillRGB(uint16_t color)
{
	lcdFilledRec(0,0,LCD_HEIGHT,LCD_WIDTH,color);
}




/***********H Line*************************************/
void lcdDrawHLine(uint16_t x0, uint16_t y, uint16_t x1, uint16_t color)
{
	// Allows for slightly better performance than setting individual pixels
	uint16_t x, pixels;

	if (x1 < x0)
	{
		// Switch x1 and x0
		x = x1;
		x1 = x0;
		x0 = x;
	}

	// Check limits
	if (x1 >= LCD_WIDTH)
	{
		x1 = LCD_WIDTH ;
	}
	if (x0 >= LCD_WIDTH)
	{
		x0 = LCD_WIDTH;
	}
	ili9341_setCol( x0, x1);
	ili9341_setPage(y, y);
	ili9341_send_command(0x2c);
	
	for (pixels = 0; pixels < x1 - x0 ; pixels++)
	{
		ili9341_send_word(color);
	}
	
}
/***********V Line*************************************/
void lcdDrawVLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color)
{
	// Allows for slightly better performance than setting individual pixels
	uint16_t y, pixels;

	if (y1 < y0)
	{
		// Switch y1 and y0
		y = y1;
		y1 = y0;
		y0 = y;
	}

	// Check limits
	if (y1 >= LCD_HEIGHT)
	{
		y1 = LCD_HEIGHT - 1;
	}
	if (y0 >= LCD_HEIGHT)
	{
		y0 = LCD_HEIGHT - 1;
	}

	ili9341_setCol( x, x);
	ili9341_setPage(y0, y1);
	ili9341_send_command(0x2c);
	
	for (pixels = 0; pixels < y1 - y0 ; pixels++)
	{
		ili9341_send_word(color);
	}

}

/* ********draw simple frame (rectangle ) *********** */
void lcdDrawRectangle(uint16_t poX, uint16_t poY, uint16_t length, uint16_t width, uint16_t color)
{
	lcdDrawHLine(poX, poY, poX + length-1, color);
	lcdDrawHLine(poX, poY + width-1, poX+length, color);
	
	lcdDrawVLine(poX, poY, poY + width-1, color);
	lcdDrawVLine(poX + length-1, poY, poY+width-1, color);
}



/* yeap, round circule */
void lcdDrawCircle(int poX, int poY, int r,uint16_t color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do {
		lcdDrawPixel(poX-x, poY+y,color);
		lcdDrawPixel(poX+x, poY+y,color);
		lcdDrawPixel(poX+x, poY-y,color);
		lcdDrawPixel(poX-x, poY-y,color);
		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);
}
void lcdFillCircle(int poX, int poY, int r,uint16_t color)
{
	int x = -r, y = 0, err = 2-2*r, e2;
	do {

		lcdDrawVLine(poX-x, poY-y, poY-y+ 2*y, color);
		lcdDrawVLine(poX+x, poY-y, poY-y+ 2*y, color);

		e2 = err;
		if (e2 <= y) {
			err += ++y*2+1;
			if (-x == y && e2 <= x) e2 = 0;
		}
		if (e2 > x) err += ++x*2+1;
	} while (x <= 0);

}


void lcdDrawChar(int x, int y, unsigned int color, unsigned int phone, unsigned char charcode, unsigned char size)
{
	switch(size)
	{
		int i,h;
		case 1:
		for(h=0;h<8;h++)
		{
			for(i=0;i<8;i++)
			{
				if ((pgm_read_byte(&chars8[charcode-0x20][h])>>(7-i))&0x01)
				{
					lcdDrawPixel(x+i,y+h,color);
				}
				else
				{
					lcdDrawPixel(x+i,y+h,phone);
				}
			}
		}
		break;
		case 2:
		for(h=0;h<16;h++)
		{
			for(i=0;i<8;i++)
			{
				if ((pgm_read_byte(&chars16[charcode-0x20][h*2])>>(7-i))&0x01)
				{
					lcdDrawPixel(x+i,y+h,color);
				}
				else
				{
					lcdDrawPixel(x+i,y+h,phone);
				}
				if ((pgm_read_byte(&chars16[charcode-0x20][h*2+1])>>(7-i))&0x01)
				{
					lcdDrawPixel(x+i+8,y+h,color);
				}
				else
				{
					lcdDrawPixel(x+i+8,y+h,phone);
				}
			}
		}
		break;
	}
}

void TFT9341_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone,
char *str, unsigned char size)
{
	while (*str)
	{
		if ((x+(size*8))>X_SIZE)
		{
			y = 1;
			x = x + (size*8);
		}
		lcdDrawChar(x,y,color,phone,*str,size);
		y += size*8;
		*str++;
	}
}