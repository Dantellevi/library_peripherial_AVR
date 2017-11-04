#include "lcd.h"
#include <avr/pgmspace.h>
#include <util/delay.h>



static void LCDcommand(uint8_t);
static void Send_byte(uint8_t);
static void Busy_flag(void);
static void HiPin(void);
static void OutPin(void);
static void InPin(void);
static void Strob(void);





//----------------------------------------------------------
//void lcd_put_Kiril(unsigned char q, unsigned char c, unsigned char m)   // запись 1 символа в GRAM lcd c-символ, m- место
//{   LCD_putbyte(((m*8)+0x40), LCD_COM);              // переход на запись символа GRAM, адрес 0x40
	//for(unsigned char d=0; d<8; d++)
	//{   if(q==0) LCD_putbyte(Kmal[c][d], LCD_DAT);    // перекидываем символ в GRAM LCD
		//if(q==1) LCD_putbyte(Kbig[c][d], LCD_DAT);    // перекидываем символ в GRAM LCD
	//}
//}


//================================================================================================


//Пользовательские функции для LCD, ими пользуемся в программе.
#if 1
void LCDdata(uint8_t i)						//Отправка символа для отображения на дисплее.
{
	Busy_flag();	//Проверим сперва флаг занятости, а свободен ли дисплей?
	CPORT|=(1<<RS); //RS=1 посылаем данные в LCD
	Send_byte(i);
	CPORT&=~(1<<RS);//RS=0
}
void LCDdataXY (uint8_t a, uint8_t b,uint8_t c)	//Вывести 1 символ на дисплей в X, Y позицию .
{
	LCDGotoXY(b,c);
	LCDdata(a);
}
void LCDGotoXY(uint8_t x,uint8_t y)			//Устанавливаем курсор в X, Y позицию
{
	 uint8_t Address;
	
	switch(y)
	{
		case 0: Address = LINE0+x; 
				break;
		case 1: Address = LINE1+x; 
				break;
		case 2: Address = LINE2+x;
				break;
		case 3: Address = LINE3+x;
				break;
		default: Address = LINE0+x;
	}
	
	LCDcommand(1<<7 | Address);
}
void LCDstringXY(char *i,uint8_t x,uint8_t y) //Вывести строку на дисплей X,Y
{
	LCDGotoXY(x,y);
	while( *i )
	{
		LCDdata(*i++ );
	}
}
void LCDsendString(char *s)//Вывести строку на дисплей.
{
	while( *s )
	{
		LCDdata(*s++ );
	}
	
}
void LCDstring_of_sramXY(uint8_t* data,uint8_t x, uint8_t y)
{
	LCDGotoXY(x,y);
	if (!data)
	{
		return;
	}
	
	uint8_t i=0;
	while(data[i] != '\0')
	{
		LCDdata(data[i]);
		i++;
	}
}
void LCDstring_of_flashXY(const uint8_t *FlashLoc,uint8_t x,uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDdata((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}
void LCDinit(void)							//Инициализируем дисплей
{
	//Перед инициализацией LCD, надо в init задержку в 100 мсек сделать, чтоб питание устаканилось. 
	_delay_ms(100);
	CDDR |=  (1<<RS)|(1<<E)|(1<<RW);   //Настройка портов 
	CPORT&=~((1<<RS)|(1<<E)|(1<<RW));  //Настройка портов 
	OutPin();						   //Настройка портов
	
	uint8_t i=0;
	while (i!=3)
	{
		#ifdef  LCD_8BIT       //отправка символа 0x30.
		        DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4)|(0<<DB3)|(0<<DB2)|(0<<DB1)|(0<<DB0);
		#else
				DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4);
		#endif
		
		Strob();
		_delay_ms(5);
		i++;
	}
	
	//Разминочный этап закончен, далее переходим к основным упражнениям.
	
	#ifdef  LCD_8BIT
			LCDcommand(0b00111000);//8ми битный интерфейс, две строки, 5x8 точек.
	#else   //Первый раз отправляем только пол старшей тетрады
			Busy_flag();
			OutPin();
			DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(0<<DB4);//4х битный интерфейс 
			Strob();
			LCDcommand(0b00101000);//Две строки, 5x8 точек.
	#endif
	
	LCDcommand(0b1100);  //Включаем дисплей + без отображения курсоров.
	LCDcommand(0b110);   //Счетчик адреса всегда будет смещаться на n+1
	LCDcommand(0b10);    //курсор в позицию 0,0 + сброс всех сдвигов
	LCDcommand(0b1);     //очистка дисплея 
	//Основные упражнения закончены. Переходим к релаксации.
}
void LCDblank(void)			//Сделать невидимой инфо на дисплее
{
	LCDcommand(0b1000);
}
void LCDnblank(void)		//Сделать видимой инфо на дисплее + отключить видимые курсоры.
{
	LCDcommand(0b1100);
}
void LCDclear(void)			//Очистка дисплея + курсор на позицию 0,0
{
	LCDcommand(0b1);
}
void LCDcursor_bl(void)		//Включить мигающий курсор
{
	LCDcommand(0b1101);
}
void LCDcursor_on(void)		//Включить подчеркивающий курсор
{
	LCDcommand(0b1110);
}
void LCDcursor_vi(void)		//Включить оба курсора
{
	LCDcommand(0b1111);
}
void LCDcursorOFF(void)		//Выключить курсор
{
	LCDcommand(0b1100);
}
void LCDacr(void)			//Cчетчик адреса всегда будет смещаться на n+1
{
	LCDcommand(0b110);
}
void LCDacl(void)			//Cчетчик адреса всегда будет смещаться на n-1
{
	LCDcommand(0b100);
}
void LCDcursorl(void)		//Сместить курсор влево на 1
{
	LCDcommand(0b10000);
}
void LCDcursorr(void)		//Сместить курсор вправо на 1
{
	LCDcommand(0b10100);
}
void LCDcursorln(uint8_t n)	//Сместить курсор влево на n символов
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10000);
	}
}
void LCDcursorrn(uint8_t n)	//Сместить курсор вправо на n символов
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10100);
	}
}
void LCDscreenl(void)		//Сместить экран влево на 1
{
	LCDcommand(0b11000);
}
void LCDscreenr(void)		//Сместить экран вправо на 1
{
	LCDcommand(0b11100);
}
void LCDscreenln(uint8_t n)	//Сместить экран влево на n символов
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11000);
	}
}
void LCDscreenrn(uint8_t n)	//Сместить экран вправо на n символов
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11100);
	}
}
void LCDscreenL(void)		//С каждым новым символом экран будет смещаться влево
{
	LCDcommand(0b101);
}
void LCDscreenR(void)		//С каждым новым символом экран будет смещаться вправо
{
	LCDcommand(0b111);
}
void LCDresshift(void)      //Установить курсор в позицию 0,0 + сброс всех сдвигов, изображение остается
{
	LCDcommand(0b10);
}

//Системные функции, их не трогаем, они для работы дисплея.
static void LCDcommand(uint8_t i)	//Отправка команды, настройка дисплея.
{
	Busy_flag();	//Проверим сперва флаг занятости, а свободен ли дисплей?
	Send_byte(i);
}
static void Send_byte(uint8_t i)	//Передача данных LCD, вызывается функциями Send_command и Send_data.-
{
	OutPin();
	
	#ifdef  LCD_8BIT
			if ((i&1)==1)
			{
				DPORT|=(1<<DB0);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB1);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB2);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB3);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB7);
			}
			
		    Strob();
			
	#else
			
			uint8_t higb = ((i&0b11110000)>>4);
			uint8_t lowb =  (i&0b00001111);
	
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
			OutPin();
	
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
	#endif
	
	HiPin();
}

//-------------------------------------------------
void lcd_put_KirilSimvol(uint8_t v,unsigned char Kmal[])	// запись 1 символа в GRAM lcd c-символ, m- место
{

	LCDcommand(0x40);
	for(unsigned char d=0; d<8; d++)
	{
	 Send_byte(Kmal[d]);
	
	}
	
}
//-------------------------------------------------
static void Busy_flag(void)		    //Проверка флага занятости
{
	InPin();
	CPORT|=(1<<RW);	  //R/W=1 читаем из LCD
	
	#ifdef  LCD_8BIT
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//Включили строб.
				asm("nop");
				asm("nop");
				
				if (!(DPIN&(1<<DB7)))//Считали и проверили флаг занятости.
				{
					i=0;
				}
				
				CPORT&=~(1<<E);//Выключили строб.
				asm("nop");
				asm("nop");						
			}
	#else
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//Включили строб.
				asm("nop");
				asm("nop");
		
				if (!(DPIN&(1<<DB7)))//Считали и проверили флаг занятости.
				{
					i=0;
				}
		
				CPORT&=~(1<<E);//Выключили строб.
				asm("nop");
				asm("nop");
				Strob();
				asm("nop");
				asm("nop");
		
			}
	#endif
	
	CPORT&=~(1<<RW);   //R/W=0 
}
static void HiPin(void)			    //Переводим порт в состояние Hi.
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
    #endif
}
static void OutPin(void)			//Переводим порт в состояние "выход".
{
	#ifdef  LCD_8BIT
			DDDR =0xFF;
			DPORT=0;
	#else
			DDDR |=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
	#endif
}
static void InPin(void)			    //Переводим порт в состояние "вход".
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0xFF;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT|=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
	#endif
}
static void Strob(void)             //Вкл/выкл строба Е
{
	CPORT|=(1<<E);//Включили строб.
	_delay_us(1);
	CPORT&=~(1<<E);//Выключили строб.
}

void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y)		//преобразование целого в вещественное число
{
char str[40];
itoa(val,str,10);

LCDstringXY(str,x,y);

}
#endif
