#include "ILI9341.h"


uint8_t TFT_Read_Data(void)
{
	uint8_t data = 0;
	DATA_DDR_0 = 0X00;	//порт на вход с подт§жкой к земле
	DATA_PORT_0 = 0x00;

	COMMAND_PORT |= (1<<LCD_DC);	 //будем читать
	COMMAND_PORT |=(1<<LCD_WR);	 //выставл§ем на ножке, отвечающей за запись 1
	COMMAND_PORT &= ~(1<<LCD_CS);    //активируем чип
	
	COMMAND_PORT &= ~(1<<LCD_RD);    //стробируем битом чтени§
	_delay_us(5);
	data = PINA;
	COMMAND_PORT |= (1<<LCD_RD);
	
	COMMAND_PORT |= (1<<LCD_CS);    //деактивируем чип
	DATA_DDR_0 = 0XFF;				//порт на выход
	return data;
}


void TFT_Send_Cmd(uint8_t cmd)
{
	COMMAND_PORT &= ~(1<<LCD_DC);   //будем слать команду
	COMMAND_PORT |= (1<<LCD_RD);	//выставл§ем на ножке, отвечающей за чтение 1
	COMMAND_PORT &= ~(1<<LCD_CS);   //активируем чип
	COMMAND_PORT&=~(1<<LCD_WR);		//стробируем битом записи
	DATA_PORT_0 = cmd;
	DATA_PORT_8=0x00;
	_delay_us(5);
	COMMAND_PORT|=(1<<LCD_WR);
	COMMAND_PORT |= (1<<LCD_CS); 
}



void TFT_Write_Data(uint8_t data)
{
	COMMAND_PORT |= (1<<LCD_DC);	//будем слать данные
	COMMAND_PORT |= (1<<LCD_RD);	//выставл§ем на ножке, отвечающей за чтение 1
	COMMAND_PORT &= ~(1<<LCD_CS);   //активируем чип
	COMMAND_PORT&=~(1<<LCD_WR);	//стробируем битом записи
	DATA_PORT_0 = data;
	DATA_PORT_8=0x00;
	_delay_us(5);
	COMMAND_PORT|=(1<<LCD_WR);
	COMMAND_PORT |= (1<<LCD_CS);    //деактивируем чип
}

void Lcd_Write_Index(uint16_t index)
{
	COMMAND_PORT &= ~(1<<LCD_DC);            //будем слать команду
	COMMAND_PORT |= (1<<LCD_RD);	          //выставл€ем на ножке, отвечающей за чтение 1
	
	COMMAND_PORT &= ~(1<<LCD_CS);            //активируем чип
	
	DATA_PORT_0 = (index & 0X00FF);	                               //через D0 шлем младший байт
	DATA_PORT_8= (index & 0XFF00)>>8;		               //затем через D7 старший
	
	COMMAND_PORT &= ~(1<<LCD_WR);	        //теперь стробируем битом записи
	_delay_us(5);
	COMMAND_PORT |= (1<<LCD_WR);
	
	COMMAND_PORT |= (1<<LCD_CS);	               //деактивируем чип
}

void TFT_Write_Data16(uint16_t data)
{
	COMMAND_PORT |=(1<<LCD_DC);	//будем слать данные
	COMMAND_PORT |= (1<<LCD_RD);	//выставл§ем на ножке, отвечающей за чтение 1

	COMMAND_PORT &= ~(1<<LCD_CS);   //активируем чип
	
	COMMAND_PORT &= ~(1<<LCD_WR);	//стробируем битом записи
	DATA_PORT_0 = (data & 0x00ff);
	DATA_PORT_8 = (data >> 8);
	_delay_us(5);
	COMMAND_PORT |= (1<<LCD_WR);
	
	COMMAND_PORT |= (1<<LCD_CS);    //деактивируем чип
}

void Lcd_Write_Reg(uint16_t lcd_reg, uint16_t lcd_data)
{
	COMMAND_PORT &= ~(1<<LCD_CS);
	Lcd_Write_Index(lcd_reg);
	TFT_Write_Data16(lcd_data);
	COMMAND_PORT |= (1<<LCD_CS);
}

void TFT_SetOrientation(uint8_t orient)
{
	TFT_Send_Cmd(0x36);
	switch (orient)
	{
		case 0: TFT_Write_Data(0x48);
		break;
		case 1: TFT_Write_Data(0x28);
		break;
		case 2: TFT_Write_Data(0x88);
		break;
		case 3: TFT_Write_Data(0xE8);
		break;
	}
	if (orient == 0 || orient == 2)
	{
		MAX_X = 239;
		MAX_Y = 319;
	}
	else
	{
		MAX_X = 319;
		MAX_Y = 239;
	}
}


void Init_ILI9341(uint8_t orient)
{
	//конфигурируем все используемые выводы как выходы
	DATA_DDR_0 = 0XFF;
	DATA_DDR_8 = 0XFF;
	COMMAND_DDR|=(1<<LCD_RES)|(1<<LCD_CS)|(1<<LCD_DC)|(1<<LCD_WR)|(1<<LCD_RD);
	
	
	COMMAND_PORT |= (1<<LCD_RES);
	_delay_ms(100);    //не больша€ задержка после включени€
	
	
	Lcd_Write_Reg(0X0007, 0X0021);   //далее записываем в регистры значени€
	Lcd_Write_Reg(0X0000, 0X0001);
	Lcd_Write_Reg(0X0007, 0X0023);
	Lcd_Write_Reg(0X0010, 0X0000);
	_delay_ms(30);
	Lcd_Write_Reg(0X0007, 0X0033);
	Lcd_Write_Reg(0X0011, 0X6838);
	Lcd_Write_Reg(0X0002, 0X0600);
	
	//TFT_Send_Cmd(0x01);		//Software Reset
	//_delay_ms(1000);
	//
//
	////Power Control 1
	//TFT_Send_Cmd(0xC0);		//зада™м градацию серого цвета
	//TFT_Write_Data(0x25);
//
//
	////Power Control 2
	//TFT_Send_Cmd(0xC1);		//настройка step up преобразовател§
	//TFT_Write_Data(0x11);
//
//
	////VCOM Control 1
	//TFT_Send_Cmd(0xC5);		//контрастность определ§етс§ разностью VCOMH - VCOML = 5.2V
	//TFT_Write_Data(0x2B);	//VCOMH = 3.825
	//TFT_Write_Data(0x2B);	//VCOML = -1.375
	//
	////VCOM Control 2
	//TFT_Send_Cmd(0xC7);		//на Vcom по сути °їЮ, а тут мы задаем offset дл§ него
	//TFT_Write_Data(0x86);   //VML=58 VMH=58
//
	////Memory Access Control
	//TFT_SetOrientation(orient);//выбираем ориентацию диспле§
	//
	////COLMOD: Pixel Format Set
	//TFT_Send_Cmd(0x3A);		//один пиксель будет кодироватьс§ 16 битами
	//TFT_Write_Data(0x05);
	//
	////Frame Rate Control
	//TFT_Send_Cmd(0xB1);
	//TFT_Write_Data(0x00);
	//TFT_Write_Data(0x18);	//Frame Rate 79Hz
//
	////Display Function Control
	//TFT_Send_Cmd(0xB6);
	//TFT_Write_Data(0x0A);
	//TFT_Write_Data(0x82);//восьмой бит определ§ет нормальный цвет кристала белый - 1, черный - 0,
	//TFT_Write_Data(0x27);
//
	//// Sleep Out
	//TFT_Send_Cmd(0x11);
//
	//_delay_ms(120);
//
	////Display On
	//TFT_Send_Cmd(0x29);
}



void TFT_Read_Id(void)
{
	char buf[40];
	TFT_Send_Cmd(0xD3);
	TFT_Read_Data();
	TFT_Read_Data();
	
	uint8_t data1=TFT_Read_Data();
	
	uint8_t data2=TFT_Read_Data();
	sprintf(buf,"ID=%u%u\r\n",data1,data2);
	Usart_PrintString(buf);

}


void TFT_Send_Data(uint16_t data)
{
	uint8_t data1 = data>>8;
	uint8_t data2 = data&0xff;
	TFT_Write_Data(data1);
	TFT_Write_Data(data2);
}

void TFT_Set_Column(uint16_t start_column,uint16_t end_colunm)
{
	TFT_Send_Cmd(0x2A);
	TFT_Send_Data(start_column);
	TFT_Send_Data(end_colunm);
}

void TFT_Set_Page(uint16_t start_page,uint16_t end_page)
{
	TFT_Send_Cmd(0x2B);
	TFT_Send_Data(start_page);
	TFT_Send_Data(end_page);
}

void TFT_Set_XY(uint16_t x, uint16_t y)
{
	TFT_Set_Column(x, x);
	TFT_Set_Page(y, y);
	TFT_Send_Cmd(0x2c);
}


void TFT_Draw_Pixel(uint16_t x, uint16_t y,uint16_t color)
{
	TFT_Set_XY(x, y);
	TFT_Write_Data16(color);
}


uint16_t constrain(uint16_t a, uint16_t b, uint16_t c)
{
	if (a < b)
	{
		return b;
	}
	if (c < a)
	{
		return c;
	}
	else return a;
}


void TFT_Fill_Screen(uint16_t x_left, uint16_t x_right, uint16_t y_up, uint16_t y_down, uint16_t color)
{
	unsigned long  xy=0;
	unsigned long i=0;
	if(x_left > x_right)
	{
		x_left = x_left^x_right;	//если координата левого кра§ больше
		x_right = x_left^x_right;	//координаты правого кра§ они помен§ютс§
		x_left = x_left^x_right;	//местами, было x_left = 5 x_right = 3
		//стало x_left = 3 x_right = 5
	}
	if(y_up > y_down)
	{
		y_up = y_up^y_down;			//то же самое дл§ оси y
		y_down = y_up^y_down;		//название этой операции
		y_up = y_up^y_down;			//"swap без временной переменной"
	}
	//контролируем, что бы передаваемые в функцию координаты
	//входили в облась допустимых значений
	x_left = constrain(x_left, MIN_X,MAX_X);
	x_right = constrain(x_right, MIN_X,MAX_X);
	y_up = constrain(y_up, MIN_Y,MAX_Y);
	y_down = constrain(y_down, MIN_Y,MAX_Y);

	xy = (x_right - x_left+1);		//рассчитываем количество точек
	xy = xy*(y_down - y_up+1);		//которое надо закрасить

	TFT_Set_Column(x_left,x_right);	//зада™м рабочую область по x
	TFT_Set_Page(y_up, y_down);		//зада™м рабочую область по y
	TFT_Send_Cmd(0x2c);				//будем писать в видео ЭЂФ
	
	for(i=0; i < xy; i++)
	{
		TFT_Write_Data16(color);	//переда™м кодировку цвета
	}
}










