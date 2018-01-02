

#include "Main.h"

unsigned char key_code[4][4]={
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};		//Внимание!!! для реальной клавиатуры расположение цифр другое



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

