/*
 * AT24Project.c
 *
 * Created: 01.02.2018 15:20:20
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

unsigned char bt[32];		//переменна€ дл€ записи в пам€ть

int main(void)
{
	 	bt[0]=0x30;	 bt[1]=0x31;  bt[2]=0x32;  bt[3]=0x33;	bt[4]=0x34;	 bt[5]=0x35;  bt[6]=0x36;	bt[7]=0x37;
	 	bt[8]=0x38;	 bt[9]=0x39;  bt[10]=0x3A; bt[11]=0x3B; bt[12]=0x3C; bt[14]=0x3D; bt[14]=0x3E; bt[15]=0x3F;
	 	bt[16]=0x40; bt[17]=0x41; bt[18]=0x42; bt[19]=0x43;	bt[20]=0x44; bt[21]=0x45; bt[22]=0x46; bt[23]=0x47;
	 	bt[24]=0x48; bt[25]=0x49; bt[26]=0x4A; bt[27]=0x4B; bt[28]=0x4C; bt[29]=0x4D; bt[30]=0x4E; bt[31]=0x4F;
   //I2CStart();
   Usart_Init(9600);
   I2C_Init();
   //I2CStart();//отправл€ем условие старта
   //Usart_char_out(TWSR);//провер€ем регистр статуса I2C
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
   //I2C_SendByte(0b10100000);//передаем адерс и бит записи(0)
   //Usart_char_out(TWSR);//провер€ем статусный регистр
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
   //I2C_SendByte(0);//переходим на 0х0000- старший байт адреса пам€ти
   //Usart_char_out(TWSR);//провер€ем регистр статуса I2C
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
   //I2C_SendByte(0);//переходим на 0х0000- старший байт адреса пам€ти
   //Usart_char_out(TWSR);//провер€ем регистр статуса I2C
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
   //I2CStop();
   //Usart_char_out(TWSR);//провер€ем регистр статуса I2C
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
//
   //_delay_ms(2000);
   //------------------«апись------------------------------
   //I2CStart();//отправл€ем условие старта
   //I2C_SendByte(0b10100000);//передаем адерс и бит записи(0)
   //I2C_SendByte(0);//переходим на 0х0000- старший байт адреса пам€ти
   //for (int j=0;j<32;j++)
   //{
		//EE_WriteByte(bt[j]);
//
   //}
   //I2CStop();
   //-------------------------------------------------------



   
   //char buf[50];
   //sprintf(buf,"%s\r\n",sb);
   //Usart_PrintString(buf);
   //Usart_char_out(0x0D);
   //Usart_char_out(0x0A);
   //-------------------------------------------------------


    while (1) 
    {
		//Usart_PrintString("Hello");
		//_delay_ms(500);
		//-------------------------------„тение------------------
		I2CStart();//Ќачинаем работу TWI
		I2C_SendByte(0b10100000);//передаем адрес устройства и бит записи (0)
		I2C_SendByte(0);//передаем старшую часть адреса §чейки пам§ти
		I2C_SendByte(0);//передаем младшую часть адреса §чейки пам§ти
		I2CStart(); //отправим условие START
		I2C_SendByte(0b10100001);//передаем адрес устройства и бит чтени§ (1)
		char sb[32];
		for (int i=0;i<=30;i++)
		{
			sb[i]=EE_ReadByte();//ѕрочитаем байт из микросхемы

		}
		sb[31]=EE_ReadLastByte(); //прочитаем байт из микросхемы
		I2CStop();
		for (int j=0;j<=31;j++)
		{
			Usart_int_out(sb[j]);
			Usart_char_out(0x0D);
			Usart_char_out(0x0A);
		}

		_delay_ms(1000);


    }
}

