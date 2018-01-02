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
//void lcd_put_Kiril(unsigned char q, unsigned char c, unsigned char m)   // ������ 1 ������� � GRAM lcd c-������, m- �����
//{   LCD_putbyte(((m*8)+0x40), LCD_COM);              // ������� �� ������ ������� GRAM, ����� 0x40
	//for(unsigned char d=0; d<8; d++)
	//{   if(q==0) LCD_putbyte(Kmal[c][d], LCD_DAT);    // ������������ ������ � GRAM LCD
		//if(q==1) LCD_putbyte(Kbig[c][d], LCD_DAT);    // ������������ ������ � GRAM LCD
	//}
//}


//================================================================================================


//���������������� ������� ��� LCD, ��� ���������� � ���������.
#if 1
void LCDdata(uint8_t i)						//�������� ������� ��� ����������� �� �������.
{
	Busy_flag();	//�������� ������ ���� ���������, � �������� �� �������?
	CPORT|=(1<<RS); //RS=1 �������� ������ � LCD
	Send_byte(i);
	CPORT&=~(1<<RS);//RS=0
}
void LCDdataXY (uint8_t a, uint8_t b,uint8_t c)	//������� 1 ������ �� ������� � X, Y ������� .
{
	LCDGotoXY(b,c);
	LCDdata(a);
}
void LCDGotoXY(uint8_t x,uint8_t y)			//������������� ������ � X, Y �������
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
void LCDstringXY(char *i,uint8_t x,uint8_t y) //������� ������ �� ������� X,Y
{
	LCDGotoXY(x,y);
	while( *i )
	{
		LCDdata(*i++ );
	}
}
void LCDsendString(char *s)//������� ������ �� �������.
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
void LCDinit(void)							//�������������� �������
{
	//����� �������������� LCD, ���� � init �������� � 100 ���� �������, ���� ������� ������������. 
	_delay_ms(100);
	CDDR |=  (1<<RS)|(1<<E)|(1<<RW);   //��������� ������ 
	CPORT&=~((1<<RS)|(1<<E)|(1<<RW));  //��������� ������ 
	OutPin();						   //��������� ������
	
	uint8_t i=0;
	while (i!=3)
	{
		#ifdef  LCD_8BIT       //�������� ������� 0x30.
		        DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4)|(0<<DB3)|(0<<DB2)|(0<<DB1)|(0<<DB0);
		#else
				DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4);
		#endif
		
		Strob();
		_delay_ms(5);
		i++;
	}
	
	//����������� ���� ��������, ����� ��������� � �������� �����������.
	
	#ifdef  LCD_8BIT
			LCDcommand(0b00111000);//8�� ������ ���������, ��� ������, 5x8 �����.
	#else   //������ ��� ���������� ������ ��� ������� �������
			Busy_flag();
			OutPin();
			DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(0<<DB4);//4� ������ ��������� 
			Strob();
			LCDcommand(0b00101000);//��� ������, 5x8 �����.
	#endif
	
	LCDcommand(0b1100);  //�������� ������� + ��� ����������� ��������.
	LCDcommand(0b110);   //������� ������ ������ ����� ��������� �� n+1
	LCDcommand(0b10);    //������ � ������� 0,0 + ����� ���� �������
	LCDcommand(0b1);     //������� ������� 
	//�������� ���������� ���������. ��������� � ����������.
}
void LCDblank(void)			//������� ��������� ���� �� �������
{
	LCDcommand(0b1000);
}
void LCDnblank(void)		//������� ������� ���� �� ������� + ��������� ������� �������.
{
	LCDcommand(0b1100);
}
void LCDclear(void)			//������� ������� + ������ �� ������� 0,0
{
	LCDcommand(0b1);
}
void LCDcursor_bl(void)		//�������� �������� ������
{
	LCDcommand(0b1101);
}
void LCDcursor_on(void)		//�������� �������������� ������
{
	LCDcommand(0b1110);
}
void LCDcursor_vi(void)		//�������� ��� �������
{
	LCDcommand(0b1111);
}
void LCDcursorOFF(void)		//��������� ������
{
	LCDcommand(0b1100);
}
void LCDacr(void)			//C������ ������ ������ ����� ��������� �� n+1
{
	LCDcommand(0b110);
}
void LCDacl(void)			//C������ ������ ������ ����� ��������� �� n-1
{
	LCDcommand(0b100);
}
void LCDcursorl(void)		//�������� ������ ����� �� 1
{
	LCDcommand(0b10000);
}
void LCDcursorr(void)		//�������� ������ ������ �� 1
{
	LCDcommand(0b10100);
}
void LCDcursorln(uint8_t n)	//�������� ������ ����� �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10000);
	}
}
void LCDcursorrn(uint8_t n)	//�������� ������ ������ �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10100);
	}
}
void LCDscreenl(void)		//�������� ����� ����� �� 1
{
	LCDcommand(0b11000);
}
void LCDscreenr(void)		//�������� ����� ������ �� 1
{
	LCDcommand(0b11100);
}
void LCDscreenln(uint8_t n)	//�������� ����� ����� �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11000);
	}
}
void LCDscreenrn(uint8_t n)	//�������� ����� ������ �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11100);
	}
}
void LCDscreenL(void)		//� ������ ����� �������� ����� ����� ��������� �����
{
	LCDcommand(0b101);
}
void LCDscreenR(void)		//� ������ ����� �������� ����� ����� ��������� ������
{
	LCDcommand(0b111);
}
void LCDresshift(void)      //���������� ������ � ������� 0,0 + ����� ���� �������, ����������� ��������
{
	LCDcommand(0b10);
}

//��������� �������, �� �� �������, ��� ��� ������ �������.
static void LCDcommand(uint8_t i)	//�������� �������, ��������� �������.
{
	Busy_flag();	//�������� ������ ���� ���������, � �������� �� �������?
	Send_byte(i);
}
static void Send_byte(uint8_t i)	//�������� ������ LCD, ���������� ��������� Send_command � Send_data.-
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
void lcd_put_KirilSimvol(uint8_t v,unsigned char Kmal[])	// ������ 1 ������� � GRAM lcd c-������, m- �����
{

	LCDcommand(0x40);
	for(unsigned char d=0; d<8; d++)
	{
	 Send_byte(Kmal[d]);
	
	}
	
}
//-------------------------------------------------
static void Busy_flag(void)		    //�������� ����� ���������
{
	InPin();
	CPORT|=(1<<RW);	  //R/W=1 ������ �� LCD
	
	#ifdef  LCD_8BIT
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//�������� �����.
				asm("nop");
				asm("nop");
				
				if (!(DPIN&(1<<DB7)))//������� � ��������� ���� ���������.
				{
					i=0;
				}
				
				CPORT&=~(1<<E);//��������� �����.
				asm("nop");
				asm("nop");						
			}
	#else
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//�������� �����.
				asm("nop");
				asm("nop");
		
				if (!(DPIN&(1<<DB7)))//������� � ��������� ���� ���������.
				{
					i=0;
				}
		
				CPORT&=~(1<<E);//��������� �����.
				asm("nop");
				asm("nop");
				Strob();
				asm("nop");
				asm("nop");
		
			}
	#endif
	
	CPORT&=~(1<<RW);   //R/W=0 
}
static void HiPin(void)			    //��������� ���� � ��������� Hi.
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
    #endif
}
static void OutPin(void)			//��������� ���� � ��������� "�����".
{
	#ifdef  LCD_8BIT
			DDDR =0xFF;
			DPORT=0;
	#else
			DDDR |=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
	#endif
}
static void InPin(void)			    //��������� ���� � ��������� "����".
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0xFF;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT|=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
	#endif
}
static void Strob(void)             //���/���� ������ �
{
	CPORT|=(1<<E);//�������� �����.
	_delay_us(1);
	CPORT&=~(1<<E);//��������� �����.
}

void LCDputsIntGotoXY(int val,uint8_t x,uint8_t y)		//�������������� ������ � ������������ �����
{
char str[40];
itoa(val,str,10);

LCDstringXY(str,x,y);

}
#endif
