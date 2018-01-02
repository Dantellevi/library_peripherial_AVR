
#ifndef SERVOPRIVODMUX_H_
#define SERVOPRIVODMUX_H_

#include "Main.h"

#define MaxServo 20

typedef struct
{
	unsigned char  Servo_portA_;
	unsigned char  Servo_portC_;
	unsigned char  Servo_portB_;
	unsigned char  Servo_portD_;
	unsigned char  Servo_Position_;
} DanieServoE;
typedef struct
{
	uint8_t Position;  //угол на который нужно здвинуть сервопривод
	uint8_t BitPorta;      //порт к которому нужно привязать данный привод
} DanieServo;

DanieServo    Servo[MaxServo];
DanieServo    *Servo_[MaxServo];
DanieServoE   Servo_W[MaxServo];
unsigned char Servo_Uctanovka[4],Servo_Dan;




void DanieServo_Port(void);
void Servo_Port_Ustanovki(void);


#endif /* SERVOPRIVODMUX_H_ */