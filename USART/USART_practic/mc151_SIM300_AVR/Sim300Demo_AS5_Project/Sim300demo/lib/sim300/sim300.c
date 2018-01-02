/******************************************************************************

                          eXtreme Electronics xAPI(TM)
						  ----------------------------
xAPI is a Powerful but easy to use C library to program the xBoard(TM)
series of AVR development board. The library has support for commonly use tasks
like:-

*LCD interfacing
*MUXED 7 segment displays.
*Remote Control
*Serial Communication
*DC Motor Controls with Speed Control
*Analog Measurement for Sensor Interface.
*Temperature Measurement.
*I2C Communication.
*EEPROM Interface
*Real Time Clock (RTC Interface)
*GSM Module Interface

The APIs are highly documented and easy to use even by a beginner.

For More Info Log On to 
www.eXtremeElectronics.co.in

Copyright 2008-2012 eXtreme Electronics India

                                    GSM Core
						           ----------
This module is used for interfacing with Standard GSM Module using the AT command
set.

                                     NOTICE
									--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

*******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include "../../lib/usart/usart.h"
#include "../../lib/lcd/lcd.h"

#include "sim300.h"

//A common buffer used to read response from SIM300
char sim300_buffer[128];

int8_t SIM300Init()
{
	//Init USART lib
	USARTInit(103);
	
	//Check communication line
	SIM300Cmd("AT");	//Test command
	
	//Now wait for response
	uint16_t i=0;
	
	//correct response is 6 byte long
	//So wait until we have got 6 bytes
	//in buffer.
	while(i<10)
	{
		if(UDataAvailable()<6)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}			
		else
		{
			//We got a response that is 6 bytes long
			//Now check it	
			UReadBuffer(sim300_buffer,6);	//Read serial Data
			
			return SIM300CheckResponse(sim300_buffer,"OK",6);
				
		}			
	}
	
	//We waited so long but got no response
	//So tell caller that we timed out
	
	return SIM300_TIMEOUT;
			
}

int8_t SIM300Cmd(const char *cmd)
{
	UWriteString(cmd);	//Send Command
	UWriteData(0x0D);	//CR
	
	uint8_t len=strlen(cmd);
	
	len++;	//Add 1 for trailing CR added to all commands
	
	uint16_t i=0;
	
	//Wait for echo
	while(i<10*len)
	{
		if(UDataAvailable()<len)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//We got an echo
			//Now check it
			UReadBuffer(sim300_buffer,len);	//Read serial Data
			
			return SIM300_OK;
			
		}
	}
	
	return SIM300_TIMEOUT;
			
}

int8_t SIM300CheckResponse(const char *response,const char *check,uint8_t len)
{
	len-=2;
	
	//Check leading CR LF
	if(response[0]!=0x0D | response[1]!=0x0A)
		return	SIM300_INVALID_RESPONSE;
	
	//Check trailing CR LF
	if(response[len]!=0x0D | response[len+1]!=0x0A)
		return	SIM300_INVALID_RESPONSE;
		
	
	//Compare the response
	for(uint8_t i=2;i<len;i++)
	{
		if(response[i]!=check[i-2])
			return SIM300_FAIL;
	}
	
	return SIM300_OK;		
}

int8_t SIM300WaitForResponse(uint16_t timeout)
{
	uint8_t i=0;
	uint16_t n=0;
	
	while(1)
	{
		while (UDataAvailable()==0 && n<timeout){n++; _delay_ms(1);}
	
		if(n==timeout)
			return 0;
		else
		{
			sim300_buffer[i]=UReadData();
		
			if(sim300_buffer[i]==0x0D && i!=0)
			{
				UFlushBuffer();
				return i+1;
			}				
			else
				i++;
		}
	}	
}

int8_t SIM300GetNetStat()
{
	//Send Command
	SIM300Cmd("AT+CREG?");
	
	//Now wait for response
	uint16_t i=0;
	
	//correct response is 20 byte long
	//So wait until we have got 20 bytes
	//in buffer.
	while(i<10)
	{
		if(UDataAvailable()<20)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//We got a response that is 20 bytes long
			//Now check it
			UReadBuffer(sim300_buffer,20);	//Read serial Data
			
			if(sim300_buffer[11]=='1')
				return SIM300_NW_REGISTERED_HOME;
			else if(sim300_buffer[11]=='2')
				return SIM300_NW_SEARCHING;
			else if(sim300_buffer[11]=='5')
				return SIM300_NW_REGISTED_ROAMING;
			else
				return SIM300_NW_ERROR;			
		}
	}
	
	//We waited so long but got no response
	//So tell caller that we timed out
	
	return SIM300_TIMEOUT;
	
}

int8_t SIM300IsSIMInserted()
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+CSMINS?");
	
	//Now wait for response
	uint16_t i=0;
	
	//correct response is 22 byte long
	//So wait until we have got 22 bytes
	//in buffer.
	while(i<30)
	{
		if(UDataAvailable()<22)
		{
			i++;
			
			_delay_ms(10);
			
			continue;
		}
		else
		{
			//We got a response that is 22 bytes long
			//Now check it
			UReadBuffer(sim300_buffer,22);	//Read serial Data
			
			if(sim300_buffer[13]=='1')
				return SIM300_SIM_PRESENT;
			else
				return SIM300_SIM_NOT_PRESENT;
		}
	}
	
	//We waited so long but got no response
	//So tell caller that we timed out
	
	return SIM300_TIMEOUT;
}

uint8_t SIM300GetProviderName(char *name)
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+CSPN?");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
		return SIM300_TIMEOUT;
	
	char *start,*end;
	start=strchr(sim300_buffer,'"');
	start++;
	end=strchr(start,'"');
	
	*end='\0';
	
	strcpy(name,start);
	
	return strlen(name);
}

int8_t SIM300GetIMEI(char *emei)
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+GSN");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
		return SIM300_TIMEOUT;
		
	sim300_buffer[len-1]='\0';
	
	strcpy(emei,sim300_buffer+2);
	
	return SIM300_OK;	
}

int8_t SIM300GetManufacturer(char *man_id)
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+GMI");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
		return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(man_id,sim300_buffer+2);//+2 for removing leading CR LF
	
	return SIM300_OK;
}

int8_t	SIM300GetModel(char *model)
{
	UFlushBuffer();
	
	//Send Command
	SIM300Cmd("AT+GMM");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(model,sim300_buffer+2);//+2 for removing leading CR LF
	
	return SIM300_OK;
}
