/*
 * SIM_300.c
 *
 * Created: 15.12.2017 9:52:40
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

extern char sim300_buffer[128];

void Halt(void);
void Port_Init(void)
{
	DDRA=0xFF;
	PORTA=0x00;

}

int main(void)
{
	Port_Init();
	LCDinit();
    Usart_Init(Usart_baud);
	LCDstringXY("SIM300 Demo !",0,0);
	_delay_ms(1000);
	//Initialize SIM300 module
	LCDstringXY("Initializing ...",0,0);
	int8_t r=SIM300Init();
	_delay_ms(1000);

	//Проверяем статус программы
	switch(r)
	{
		case SIM300_OK:
		LCDstringXY("OK !",0,1);
		break;
		case SIM300_TIMEOUT:
		LCDstringXY("No response",0,1);
		
		Halt();
		case SIM300_INVALID_RESPONSE:
		LCDstringXY("Inv response",0,1);
		
		Halt();
		case SIM300_FAIL:
		LCDstringXY("Fail",0,1);
		
		Halt();
		default:
		LCDstringXY("Unknown Error",0,1);
		
		Halt();
	}


	
	_delay_ms(1000);

	//IMEI No display
	LCDclear();
	
	char imei[16];
	
	r=SIM300GetIMEI(imei);
	if(r==SIM300_TIMEOUT)
	{
		LCDstringXY("Comm Error !",0,0);
		Halt();
	}
	else{
	LCDstringXY("Device IMEI:",0,0);
	LCDstringXY(imei,0,1);
	}
	_delay_ms(1000);

	//Manufacturer ID
	LCDclear();
	
	char model[48];
	
	r=SIM300GetModel(model);
	
	if(r==SIM300_TIMEOUT)
	{
		LCDstringXY("Command Error !",0,0);
		Halt();
	}
	else{
		LCDstringXY("Model:",0,1);
		LCDstringXY(model,8,1);
		
	}
	
	_delay_ms(1000);
	
	//Проверка сим-карты
	LCDclear();
	LCDstringXY("Checking SIMCard",0,1);
	
	_delay_ms(1000);
	
	r=SIM300IsSIMInserted();
	
	if (r==SIM300_SIM_NOT_PRESENT)
	{
		//Отсутствует симкарта
		LCDstringXY("No SIM Card !",0,1);
		
		Halt();
	}
	else if(r==SIM300_TIMEOUT)
	{
		//Ошибка соединения
		LCDstringXY("Comm Error !",0,1);
		
		Halt();
	}
	else if(r==SIM300_SIM_PRESENT)
	{
		//Обнаружена симкарты
		LCDstringXY("SIM Card Present",0,1);
		
		_delay_ms(1000);
	}

	//Network search
	LCDclear();
	LCDstringXY("SearchingNetwork",0,0);
	
	uint8_t		nw_found=0;
	uint16_t	tries=0;
	uint8_t		x=0;
	
	while(!nw_found)
	{
		r=SIM300GetNetStat();
		
		if(r==SIM300_NW_SEARCHING)
		{
			LCDstringXY("%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0",0,1);
			LCDstringXY("%1",x,1);
			LCDGotoXY(17,1);
			
			x++;
			
			if(x==16) x=0;
			
			_delay_ms(50);
			
			tries++;
			
			if(tries==600)
			break;
		}
		else
		break;
		
	}
	LCDclear();
	
	if(r==SIM300_NW_REGISTERED_HOME)
	{
		LCDstringXY("Network Found",0,2);
	}
	else
	{
		LCDstringXY("Cant Connt to NW!",0,1);
		Halt();
	}
	
	_delay_ms(1000);
	
	LCDclear();
	
	//показать имя провайдера
	char pname[32];
	r=SIM300GetProviderName(pname);
	
	if(r==0)
	{
		LCDstringXY("Comm Error !",0,1);
		Halt();
	}
	
	LCDstringXY(pname,0,1);
	
	_delay_ms(1000);
	
	Halt();

   
}


void Halt(void)
{
while(1)
{
	
}
}

