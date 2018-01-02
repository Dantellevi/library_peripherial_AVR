

#include "Main.h"

int main(void)
{
   Servo[0].BitPorta=0xA6;
   Servo[1].BitPorta=0xB0;
   Servo[2].BitPorta=0xC6;
   Servo[3].BitPorta=0xD0;
   Servo[4].BitPorta=0xA7;
   Servo[5].BitPorta=0xC7;
   Servo[6].BitPorta=0xD1;
   Servo[7].BitPorta=0xB1;
   Servo[8].BitPorta=0xA2;
   Servo[9].BitPorta=0xC2;
   Servo[10].BitPorta=0xB2;
   Servo[11].BitPorta=0xD2;
   Servo[12].BitPorta=0xA3;
   Servo[13].BitPorta=0xB3;
   Servo[14].BitPorta=0xC3;
   Servo[15].BitPorta=0xD3;
   Servo[16].BitPorta=0xA4;
   Servo[17].BitPorta=0xB4;
   Servo[18].BitPorta=0xC4;
   Servo[19].BitPorta=0xD4;
   //-----------------------------------------
   Servo[0].Position=125;
   Servo[1].Position=125;
   Servo[2].Position=100;
   Servo[3].Position=80;
   Servo[4].Position=75;
   Servo[5].Position=75;
   Servo[6].Position=70;
   Servo[7].Position=70;
   Servo[8].Position=110;
   Servo[9].Position=110;
   Servo[10].Position=105;
   Servo[11].Position=105;
   Servo[12].Position=100;
   Servo[13].Position=80;
   Servo[14].Position=130;
   Servo[15].Position=135;
	Servo[16].Position=145;
	Servo[17].Position=150;
	Servo[18].Position=150;
	Servo[19].Position=155;
	//================================================
	Servo_Port_Ustanovki();
	sei();

    while (1) 
    {
		DanieServo_Port();

    }
}

