#include "MatrixKeyBoard.h"

unsigned char valueKeyboard=' ';

unsigned char cnt=0;
 char passconfim[4];

 //�������� �������� � ��������� ����������
unsigned char GetMatrixValue(void)
{
		return valueKeyboard;
	
}

//������� �������� ������ � ����� ����������
void Password_Print_Confim(void)
{
	unsigned char flag_compare=0;
	if (GetMatrixValue()!=' ' && GetMatrixValue()!='*'&& GetMatrixValue()!='#')
	{
		passconfim[cnt]=GetMatrixValue();
		LCDdataXY('*',cnt,1);
		cnt++;
		_delay_ms(250);
		valueKeyboard=' ';
	}
	else if (GetMatrixValue()=='*')
	{
		if (cnt==4)
		{
			if (passconfim[0]=='1')	//������ ����� ������
			{
				flag_compare++;
			}
			if (passconfim[1]=='2')//������  ����� ������
			{
				flag_compare++;
			}
			if (passconfim[2]=='3')//������ ����� ������
			{
				flag_compare++;
			}
			if (passconfim[3]=='4')//��������� ����� ������
			{
				flag_compare++;
			}
			

			if (flag_compare==4)
			{
				LCDstringXY("Password OK   ",1,2);
				
				//--------------------�������������� ��� ���� ������ �����------------------------------

				//-------------------------------------------------------------------------------------------
				
			}
			else{

				LCDstringXY("Password Error",1,2);
				cnt=0;
				valueKeyboard=' ';
				flag_compare=0;
				for(int i=0;i<4;i++)
				{
					passconfim[i]=0;
				}
				_delay_ms(1000);
				LCDclear();
			}
			
			
		}
		else
		{
			LCDstringXY("Error !!password!!!",1,3);
			//--------------------�������������� ��� ���� ��������� ������------------------------------

			//-------------------------------------------------------------------------------------------
		}
	}
	else if (GetMatrixValue()=='#')
	{
		cnt=0;
		valueKeyboard=' ';
		flag_compare=0;
		for(int i=0;i<4;i++)
		{
			passconfim[i]=0;
		}

		LCDclear();
		LCDstringXY("reset !!",1,3);
		_delay_ms(1000);
		LCDclear();
		
	}
	
	


}