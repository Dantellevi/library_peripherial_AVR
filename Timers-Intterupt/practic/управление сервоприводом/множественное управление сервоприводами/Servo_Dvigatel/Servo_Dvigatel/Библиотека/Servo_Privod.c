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
		          uint8_t Position;  //���� �� ������� ����� �������� �����������
		          uint8_t BitPorta;      //���� � �������� ����� ��������� ������ ������				
		        } DanieServo;				
			
DanieServo    Servo[MaxServo];
DanieServo    *Servo_[MaxServo];
DanieServoE   Servo_W[MaxServo];
unsigned char Servo_Uctanovka[4],Servo_Dan;
