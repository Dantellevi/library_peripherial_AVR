#define LCD_CLR lcd_clr ();
#define LCD_LINE1 0x02 //upper line start
#define LCD_START 0x30 //LCD START
#define LCD_NO_CURS 0x0C  //display on, no cursor
#define LCD_DISP_OFF 0x08  //display off, no cursor
#define LCD_MODE_4 0x28 //4 bit data, 2 lines, 5x8
#define LCD_ 0x02
#define LCD_LINE2 0xA8  //bottom line start

//LCD functions------------------

void lcd_com (uint8_t cmd1)
	{
	LCD_PORT = ((cmd1 & 0xF0)); //RS=0 - it's command
	LCD_PORT |= (1<<E);
	asm ("nop");
	LCD_PORT  &=~(1<<E);
	LCD_PORT = ((cmd1 & 0x0F)<<4); //Write low tetrade, RS, E to port
	LCD_PORT |= (1<<E); //Write low tetrade to LCD
	asm ("nop");
	LCD_PORT &=(~(1<<E));
	LCD_DELAY;
	}

void lcd_data (uint8_t cmd1)
	{
	LCD_PORT=((cmd1 & 0xF0));
	LCD_PORT|= ((1<<E)|(1<<RS)); //RS=1 - it's data Write higth tetrade to LCD
	asm ("nop");
	LCD_PORT&=~(1<<E);
	LCD_PORT = ((cmd1 & 0x0F)<<4); //Write low tetrade, RS, E to port 
	LCD_PORT|= ((1<<E)|(1<<RS)); //RS=1 - it's dataWrite low tetrade to LCD
	asm ("nop");
	LCD_PORT&=~(1<<E);
	LCD_DELAY;
	}

void init_lcd (void)
	{
	lcd_com (LCD_START);
	lcd_com (LCD_MODE_4);
	lcd_com (LCD_NO_CURS);	
	}

void lcd_clr ()
	{
	lcd_com (0x01);
	LCD_DELAY;
	}

void lcd_string (char *s)
	{
	while  (*s!='\n') 
		lcd_data (*s++);
	}

void lcd_hex_out (char sim)
	{
	uint8_t tmp;
	tmp = ((sim & 0xF0) >> 4); //first sim
	if (tmp >= 0x0A) tmp += 7; //if simbol (ascii)
	tmp += 0x30;    //add ascii
	lcd_data (tmp);
	tmp = sim & 0x0F; //second sim
	if (tmp >= 0x0A) tmp += 7; //if simbol (ascii)
	tmp += 0x30;    //add ascii
	lcd_data (tmp);
	}
//END LCD functions--------------
