#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "confm16.h"


#include "lcd.h"
#include "gsm_fun.h"


int main (void)
	{
	uint8_t tmp;
	init_all ();
	LED_LGT;
	init_lcd ();
	LONG_DELAY;
	LCD_CLR;
	if (!send_sms (1,NUM0)) ErrMes ();
	LONG_DELAY;
	Ready_Snd ();
	ERR_OFF;
 	while (1)
		{
		if (mess != 0) //if we have mess in buffer
			{
			// code 
			mess--;   //minus one
			rx_check_in ();
			if (com_detect == 2) 
				{
				if (!send_sms (1,NUM0)) ErrMes ();
				}
			com_detect = 0;
			}
		tmp = PINC & 1;  //If push button:
		if (tmp != 1)
			{
			send_sms(0,NUM0);
			Ready_Snd ();
			}
		}
	return 0;
	}
