
#include "Main.h"




int main(void)
{
	lcd_init(0);
	port_ini();
	//lcd_gotoxy(0,0);
	//lcd_str_out("Hello!!!");
   //lcd_printStringXY("Privet mir",1,1);
   //unsigned char i;
   //char str[10];
   FATFS fs; //FatFs объект
   FRESULT res; //Результат выполнения
   WORD s1;
   //char buffer[512] ="Selection of RAM is set by the previous address set instruction. If the address set instruction of RAM is not performed before this instruction, the data that has been read first is invalid, as the direction of AC is not yet determined. If RAM data is read several times without RAM address instructions set before, read operation, the correct RAM data can be obtained from the second. But the first data would be incorrect, as there is no time margin to transfer RAM data. In case of DDRAM read operation The..."; //Буфер данных для записи/чтения
    char buffer2[512] ={}; //Буфер данных для чтения
   //unsigned char result;
   //result=SD_Init();
   //---------------------------------------------------------------------------------------------------
   //sprintf(str,"%d",result);
   //lcd_clear();
   //lcd_gotoxy(0,0);
   //lcd_str_out(str);

   //result=SD_Write_Block(buffer,0x00,0x00,0x04,0x00);//Запишем блок из буфера
   //sprintf(str,"%d",result);
   //lcd_gotoxy(0,1);
//
   //lcd_str_out(str);
//
   //result=SD_Read_Block(buffer,0x00,0x00,0x04,0x00); //Считаем блок в буфер
   //sprintf(str,"%d",result);
    //lcd_gotoxy(0,2);
   //lcd_str_out(str);
   //-------------------------------------------------------------------------------------
  
   //result=SD_Read_Block(buffer2,0x00,0x00,0x04,0x00); //Считаем блок в буфер
   //sprintf(str,"%d",result);
//
   //lcd_gotoxy(0,2);
//
   //lcd_str_out(str);
//
   //_delay_ms(1000);
   //lcd_clear();
   //for (i=0;i<=22;i++)	
   //{
	//LCD_PrintLongStrring(buffer2+i*20);
	//_delay_ms(1000);
   //}
  //------------------------------------------------------------------------------------------------------------
  //-------------------------^-------Чтение из файла--------------------------------------------------
  lcd_clear();
  asm("nop");
  res=pf_mount(&fs); //Монтируем FAT
  //sprintf(str,"%d",res);
  //lcd_printStringXY(str,0,0);
  if(res==FR_OK) lcd_printStringXY("Done",0,0);
  else lcd_printStringXY("Error",0,0);
  _delay_ms(1000);
  lcd_printStringXY("Open file:",0,3);
  res=pf_open("1.txt");//Попытка открыть файл 1.txt
  if(res==FR_OK)
  {
	lcd_printStringXY("Done",13,3);
  }
  else lcd_printStringXY("Error",13,3);
  _delay_ms(2000);
  lcd_printStringXY("Move pointer",0,2);
  res=pf_lseek(0); //Установим курсор чтения на 0 в 1\.txt
   if(res==FR_OK)
   {
	   lcd_printStringXY("Done",13,3);
   }
   else lcd_printStringXY("Error",13,3); 
   _delay_ms(2000);
   lcd_printStringXY("Read File:",0,3);
   res=pf_read(buffer2,128,&s1);
   if(res==FR_OK)
   {
	   lcd_printStringXY("Done",13,3);
   }
   else lcd_printStringXY("Error",13,3);
   _delay_ms(2000);
   lcd_clear();
   lcd_gotoxy(0,0);
   LCD_PrintLongStrring(buffer2);
   lcd_gotoxy(0,1);
   _delay_ms(2000);
   lcd_clear();
   //--------------------------------------------------------------------------------------------------------------
   lcd_str_out("Unmout SD....");
   res=pf_mount(0x00);//демонтируем файловую систему
   if (res==FR_OK)
   {
	lcd_str_out("Done");
   }
   else
   {
	lcd_str_out("Error");
   }

   _delay_ms(1000);
   //-----------------------


   lcd_gotoxy(0,2);
   lcd_str_out("Mout SD");
   res=pf_mount(&fs);	//монтируем систему
   if (res==FR_OK)
   {
	   lcd_str_out("Done");
   }
   else
   {
	   lcd_str_out("Error");
   }
   _delay_ms(1000);
   //------------------------
   lcd_gotoxy(0,3);
   lcd_str_out("Open File...");//открываем файл для записи
   res=pf_open("1.txt");//Попытка открыть файл 1.txt
   if (res==FR_OK)
   {
	   lcd_str_out("Done");
   }
   else
   {
	   lcd_str_out("Error");
   }
   _delay_ms(1000);
   //---------------------

   lcd_gotoxy(0,1);
   lcd_str_out("Move pointer..");
   res=pf_lseek(0);	//устанавливаем курсор чтения на 0 в 1.txt
   if (res==FR_OK)
   {
	   lcd_str_out("Done");
   }
   else
   {
	   lcd_str_out("Error");
   }
   //---------------------------------------

   lcd_printStringXY("Read File:",0,3);
   res=pf_read(buffer2,128,&s1);
   if(res==FR_OK)
   {
	   lcd_printStringXY("Done",13,3);
   }
   else lcd_printStringXY("Error",13,3);
   _delay_ms(2000);
   _delay_ms(2000);
   //--------------------------
   sprintf(buffer2,"World Hello!");

   lcd_clear();
   lcd_gotoxy(0,0);
   //---------------------------

   lcd_str_out("Write Data...");
   res=pf_write(buffer2,strlen(buffer2),&s1);
   if(res==FR_OK)
   {
	   lcd_printStringXY("Done",13,3);
   }
   else lcd_printStringXY("Error",13,3);
   _delay_ms(2000);

   //---------------------------------
   lcd_clear();
   lcd_gotoxy(0,1);
   lcd_str_out("Finalise...");
   res=pf_write(0,0,&s1);//Финализируем файл 1.txt
   if(res==FR_OK)
   {
	   lcd_printStringXY("Done",13,3);
   }
   else lcd_printStringXY("Error",13,3);
   _delay_ms(2000);

   
   lcd_gotoxy(0,1);
   _delay_ms(2000);
   lcd_clear();
   //--------------------------------------------
   lcd_str_out("Unmout SD....");
   res=pf_mount(0x00);//демонтируем файловую систему
   if (res==FR_OK)
   {
	   lcd_str_out("Done");
   }
   else
   {
	   lcd_str_out("Error");
   }

   _delay_ms(1000);
   lcd_clear();
	while (1) 
    {

    }
}

