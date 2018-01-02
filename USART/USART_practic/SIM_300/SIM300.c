#include "SIM300.h"

#define ENTER 0x0D
#define CTRL_Z 0x1A

char sim300_buffer[128];		//������ ��� ���������� ������� �� SIM300

int8_t SIM300Init(void)
{
	//������������� USART-����������
	Usart_Init(Usart_baud);
	
	//�������� ����� ����� � SIM300
	SIM300Cmd("AT");	//�������� ������ �� SIM300
	
	//���������� ������ ��� �������� ������
	uint16_t i=0;
	
	//������ ������ ���������� 6 ����
	//������� 6 ����
	//��������� �� � ������
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
			//�������� ����� �� 6 ����
			//��������
			UReadBuffer(sim300_buffer,6);	//������ ������ �� �������
			
			return SIM300CheckResponse(sim300_buffer,"OK",6);
			
		}
	}
	
	//�������� ��� ������
	//��������� ����� �������� �����
	
	return SIM300_TIMEOUT;
	
}


//=====================������� �������� ������� �� ������======================
/*
		����������� ��������  :
		int8_t- ��������� ���� �������� �������� � ������ ������� ���� ������ �������� � ������
		��� �� � ������ sim300_buffer  -������������ ����� �� ������ ��� �������� ��������
*/

int8_t SIM300Cmd(char *cmd)
{
	USART_WriteString(cmd);	//�������� �������
	Usart_Transmit_SendChar(0x0D);	//������ �������� ������
	
	uint8_t len=strlen(cmd);
	
	len++;	//���������  1 ��� ��������� CR, ������������ �� ���� ��������
	
	uint16_t i=0;
	
	//������� ������
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
			//�������� �����
			//�������� 
			UReadBuffer(sim300_buffer,len);	//������ ������ �� �������
			
			return SIM300_OK;
			
		}
	}
	
	return SIM300_TIMEOUT;
	
}


/*
		=============����� �������� ������ (�������� ������)=====================

*/
int8_t SIM300CheckResponse(const char *response,const char *check,uint8_t len)
{
	len-=2;
	
	//�������� �� �������� �������� CR LF(���� �������� �� ����� 0x0D � 0x0A �� ������ �� �������� �����)
	if((response[0]!=0x0D)|(response[1]!=0x0A))
	return	SIM300_INVALID_RESPONSE;
	
	//�������� ����� ������� CR LF(���� �������� �� ����� 0x0D � 0x0A �� ������ �� �������� �����)
	if((response[len]!=0x0D)|(response[len+1]!=0x0A))
	return	SIM300_INVALID_RESPONSE;
	
	
	//���������� ������
	for(uint8_t i=2;i<len;i++)
	{
		if(response[i]!=check[i-2])
		return SIM300_FAIL;
	}
	
	return SIM300_OK;
}

//=============������� ������� �������� �������� ������ �� ������================

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
			sim300_buffer[i]=USART_ReadData();
			
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


//========================�������� ��� ����������� � ����=======================

int8_t SIM300GetNetStat(void)
{
	//�������� �������
	SIM300Cmd("AT+CREG?");//�������� ��� ����������� � ����
	
	//������� ������(���������� ��� �������)
	uint16_t i=0;
	
	//�������� 20 ���� ������
	//������� ��������� 20 ���� ������
	//� ������
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
			//�������� ����� �� 20 ���� ������
			//��������� ������
			UReadBuffer(sim300_buffer,20);	//������ ������ �� �������
			
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
	
	//���� ������ ���
	//���������� ����������� � ��������� ������� ��������
	
	return SIM300_TIMEOUT;
	
}


//=======================��������� ������������� �������� ����� ��������=========

int8_t SIM300IsSIMInserted()
{
	UFlushBuffer();
	
	//�������� ������� �� ������
	SIM300Cmd("AT+CSMINS?");
	
	//������� ������
	uint16_t i=0;
	
	//����� ������ �������� �� 22 ����
	//�������� ����� � �������� ��� � ������
	
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
			//������ � ������ � ��������
			
			UReadBuffer(sim300_buffer,22);	//������ � ������
			
			if(sim300_buffer[13]=='1')
			return SIM300_SIM_PRESENT;		//SIM-����� ������������
			else
			return SIM300_SIM_NOT_PRESENT;	//��� SIM-�����
		}
	}
	
	//������ ��������
	
	return SIM300_TIMEOUT;
}


/*
--------------------������� �������� ����� ����������------------------------
*/
uint8_t SIM300GetProviderName(char *name)
{
	UFlushBuffer();
	
	//���������� ������� �� ������ ����������
	SIM300Cmd("AT+CSPN?");
	
	uint8_t len=SIM300WaitForResponse(1000);		//������������� ����� ��������
	
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

/*
-------------------������ IMEI ������--------------------------
*/

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


/*
---------------------�������� ����������� �������������-------------------------
*/
int8_t SIM300GetManufacturer(char *man_id)
{
	UFlushBuffer();
	
	//������� �� ��������� ����� �������������
	SIM300Cmd("AT+GMI");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(man_id,sim300_buffer+2);//��������� \r\n
	
	return SIM300_OK;
}


/*
--------------------������� ������� ������������ ������------------------------
*/
int8_t	SIM300GetModel(char *model)
{
	UFlushBuffer();
	
	//������������� ������
	SIM300Cmd("AT+GMM");
	
	uint8_t len=SIM300WaitForResponse(1000);
	
	if(len==0)
	return SIM300_TIMEOUT;
	
	sim300_buffer[len-1]='\0';
	
	strcpy(model,sim300_buffer+2);//��������� \r\n
	
	return SIM300_OK;
}

void Clear_Usart_Buffer(void)
{
	
	memset(sim300_buffer,0,sizeof(sim300_buffer));
	

}


unsigned char Send_SMS(char* massage,char* NumberPhone)
{

//=====================��������   ������� �� ������ � ��������� ������==========================
	Clear_Usart_Buffer();
	strcat(NumberPhone,"\n");
	
	
	//�������� ����� ����� � SIM300
	SIM300Cmd("AT+CMGF=1\n");	//������� �� �������� ��������� � ��������� ������

	char compFlag=strcmp(sim300_buffer,"AT+CMGF=1\n");
	if (compFlag==0)
	{
		//������ ������ ��<Enter>
		//����� ���������� ��������� �� ��������� �����
		//������ ��������(AT+CMGS=����� ��������+Enter)
		SIM300Cmd(strcat("AT+CMGS=",NumberPhone));
		//������ ��������(message+0x1A)
		USART_WriteString(massage);Usart_Transmit_SendChar(CTRL_Z);

		return SIM300_SendMessage_OK;
	}
	else
	{
		return SIM300_SendMessage_ERROR;
	}


	
	

}

void Recieve_SMS(char* Buffer)
{
	UReadBuffer(sim300_buffer,10);
	char  flagcomp=strcmp(sim300_buffer,"+CMTI:'SM',1");
	if (flagcomp==0)
	{
	//�������� ������ ������������� ���������
	SIM300Cmd("AT+CMGL='REC UNREAD'");	//������� �� �������� ��������� � ��������� ������
	UReadBuffer(sim300_buffer,128);
	Buffer=(char*)sim300_buffer;

	}
}

