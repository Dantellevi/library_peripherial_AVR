/*
 * Sim300Demo.c
 *
 * Created: 10-07-2012 PM 12:23:08
 *  Author: Avinash
 */


#include <avr/io.h>
#include <util/delay.h>

#include "lib/lcd/lcd.h"
#include "lib/sim300/sim300.h"


void Halt();
int main(void)
{
   //Initialize LCD Module
   LCDInit(LS_NONE);

   //Intro Message
   LCDWriteString("SIM300 Demo !");
   LCDWriteStringXY(0,1,"By Avinash Gupta");

   _delay_ms(1000);

   LCDClear();


   //Initialize SIM300 module
   LCDWriteString("Initializing ...");
   int8_t r= SIM300Init();

   _delay_ms(1000);

   //Check the status of initialization
   switch(r)
   {
      case SIM300_OK:
         LCDWriteStringXY(0,1,"OK !");
         break;
      case SIM300_TIMEOUT:
         LCDWriteStringXY(0,1,"No response");
         Halt();
      case SIM300_INVALID_RESPONSE:
         LCDWriteStringXY(0,1,"Inv response");
         Halt();
      case SIM300_FAIL:
         LCDWriteStringXY(0,1,"Fail");
         Halt();
      default:
         LCDWriteStringXY(0,1,"Unknown Error");
         Halt();
   }

   _delay_ms(1000);

   //IMEI No display
   LCDClear();

   char imei[16];

   r=SIM300GetIMEI(imei);

   if(r==SIM300_TIMEOUT)
   {
      LCDWriteString("Comm Error !");
      Halt();
   }

   LCDWriteString("Device IMEI:");
   LCDWriteStringXY(0,1,imei);

   _delay_ms(1000);

   //Manufacturer ID
   LCDClear();

   char man_id[48];

   r=SIM300GetManufacturer(man_id);

   if(r==SIM300_TIMEOUT)
   {
      LCDWriteString("Comm Error !");
      Halt();
   }

   LCDWriteString("Manufacturer:");
   LCDWriteStringXY(0,1,man_id);

   _delay_ms(1000);

   //Manufacturer ID
   LCDClear();

   char model[48];

   r=SIM300GetModel(model);

   if(r==SIM300_TIMEOUT)
   {
      LCDWriteString("Comm Error !");
      Halt();
   }

   LCDWriteString("Model:");
   LCDWriteStringXY(0,1,model);

   _delay_ms(1000);



   //Check Sim Card Presence
   LCDClear();
   LCDWriteString("Checking SIMCard");

   _delay_ms(1000);

   r=SIM300IsSIMInserted();

   if (r==SIM300_SIM_NOT_PRESENT)
   {
      //Sim card is NOT present
      LCDWriteStringXY(0,1,"No SIM Card !");

      Halt();
   }
   else if(r==SIM300_TIMEOUT)
   {
      //Communication Error
      LCDWriteStringXY(0,1,"Comm Error !");

      Halt();
   }
   else if(r==SIM300_SIM_PRESENT)
   {
      //Sim card present
      LCDWriteStringXY(0,1,"SIM Card Present");

      _delay_ms(1000);
   }

   //Network search
   LCDClear();
   LCDWriteStringXY(0,0,"SearchingNetwork");

   uint8_t     nw_found=0;
   uint16_t tries=0;
   uint8_t     x=0;

   while(!nw_found)
   {
      r=SIM300GetNetStat();

      if(r==SIM300_NW_SEARCHING)
      {
         LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
         LCDWriteStringXY(x,1,"%1");
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
   LCDClear();

   if(r==SIM300_NW_REGISTERED_HOME)
   {
      LCDWriteString("Network Found");
   }
   else
   {
      LCDWriteString("Cant Connt to NW!");
      Halt();
   }

   _delay_ms(1000);

   LCDClear();

   //Show Provider Name
   char pname[32];
   r=SIM300GetProviderName(pname);

   if(r==0)
   {
      LCDWriteString("Comm Error !");
      Halt();
   }

   LCDWriteString(pname);

   _delay_ms(1000);

   Halt();
}

void Halt()
{
   while(1);
}