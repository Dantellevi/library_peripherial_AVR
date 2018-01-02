/*
 * Matrix_KeyBoard.c
 *
 * Created: 27.11.2017 9:04:39
 * Author : Dante_L_Levi
 */ 

#include "Main.h"

unsigned char key_code[4][3]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};



void pause(unsigned int a)
{
	unsigned int i;
	for(i=a;i>0;i--);

}

int main(void)
{

    LCDinit();
	LCDstringXY("Hello",0,0);
	Timer0_init(0,NORMAL_MODE,0,FLAG_DEL_64);
    while (1) 
    {
		Password_Print_Confim();
    }
}

