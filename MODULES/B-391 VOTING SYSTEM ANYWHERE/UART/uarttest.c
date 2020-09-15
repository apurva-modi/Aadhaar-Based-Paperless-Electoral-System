#include "LPC214x.H"                        /* LPC21xx definitions */
#include "type.h"
#include "irq.h"
#include "uart.h"
#include "target.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "lcd_arm.h"
#include "Serial.h"
#include "delay.h"
#include "wifi.h"
#include "SOFTUART.h"
#include <stdio.h>

extern DWORD UART0Count;
extern BYTE UART0Buffer[BUFSIZE];
extern DWORD UART1Count;
extern BYTE UART1Buffer[BUFSIZE];
#define UART0_HOST_BAUD  9600
#define UART1_HOST_BAUD  9600

#define SW (1 << 25)

void FINGER_ENROL(void);
void FACE_VERIFYING(void);
void FACE_VERIFYING_1(void);
void FACE_VERIFYING_2(void);
void FACE_VERIFYING_3(void);


unsigned char a[16]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};
unsigned char b[10],i=0,j,c = 0;
unsigned char a1[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x16,0x00,0x1a};
unsigned char a2[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x01,0x00,0x05};
unsigned char a3[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x01,0x00,0x08};
unsigned char a4[17]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x1b,0x01,0x00,0x00,0x00,0xa3,0x00,0xc8}; 
unsigned char a5[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x02,0x00,0x09};
unsigned char a6[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x02,0x00};



char loadval,loadbuff[10],final_load[10];

int temp,item=0,acc_1 = 500 , acc_2 = 500,d=1,ID;
unsigned char *p1,*p2;
unsigned char GPRS_GRM[20];

unsigned char buf[20],buff_1[100];
//unsigned char a[10],count1 =0,count2 =0, buff[15];
int x;

void PEOPLE_SERACHING_FINGER(void);

//void putSLcd(unsigned char *st) 
//{
//	for( ;*st ;lcd_putchar(*st++) );
//}


void ms_delay(int i)
{
	int j,k;
	for(j=0;j<i;j++)
	for(k=0;k<1275;k++);
}


int main (void)
{
 	unsigned char KG[10],ch,buff[10]; 
  	int val ,i;
  	float kg = 0.00;
	IO0DIR &= ~SW;

  	// init_VIC();
	init_lcd();
//	uart0_init();  	
	uart1_init(); 
	soft_uart_init();
    UARTInit(UART0,UART_BAUD(UART0_HOST_BAUD));
	UARTSend(UART0, "UART0\r\n", sizeof("UART0\r\n"));

 
    lcd_command_write(1);
	lcd_command_write(0x80);
	lcd_putstring(0,0,"ANYWHERE VOTING");
	lcd_command_write(0xc0);
	lcd_putstring(1,0,"SYSTEM....");
	
	ms_delay(10000);
	lcd_command_write(1);
	lcd_command_write(0x80);
	lcd_putstring(0,0,"Searching");
	lcd_command_write(0xc0);
	lcd_putstring(1,0,"Signal........");
	if(!(IO0PIN & SW))
	{
		c = 1;

		FINGER_ENROL();
		FINGER_ENROL();
		FINGER_ENROL();
			FINGER_ENROL();
		delay(10000);

	}
//	lcd_command_write(1);
//	lcd_putstring(LINE1,POS0,"YOU ARE PERSON ",LINE2,POS0,"PRESS...");
//		delay(10000); 
//	lcd_command_write(1);
//	lcd_putstring(LINE1,POS0,"2.AUTHORIZED ",LINE2,POS0,"3.UNATHORIZED");
//
//	delay(10000); 
//
//	init_key();	
	   intWIFI();
//	 //  	intWIFI();
//	 				WIFI_UPLOAD_3();
//					 intWIFI();
//					WIFI_UPLOAD_1();
//					 intWIFI();
//					 	WIFI_UPLOAD_2();
//						intWIFI();
					 //	WIFI_UPLOAD_4();


    while (1) 
    {	
		  PEOPLE_SERACHING_FINGER();
	
	}
}


void PEOPLE_SERACHING_FINGER(void)
{
	int z = 1;
	while(z)
	{
	  ID = FINGER_SCAN();
	  switch(ID)
	  {	
		case 1:lcd_clear();
			   	lcd_putstring(0,0,"USER1 ");
			//	lcd_putstring(1,0,"SYSTEM..... ");
				delay(10000);
				z=0;
			//	lcd_clear();
			//    lcd_putstring(LINE1,POS0,"WAIT FACE",LINE2,POS0,"AUTHENTICATING");
				lcd_clear();
			   	lcd_putstring(0,0,"WAIT FACE");
				lcd_putstring(1,0,"AUTHENTICATING");
				delay(10000);
				FACE_VERIFYING();
				//cash_handling_finger();
				delay(5000);
				break;

		 case 2:lcd_clear();
			   	lcd_putstring(0,0,"USER2 ");
				delay(10000);
				z=0;
					lcd_clear();
			   	lcd_putstring(0,0,"WAIT FACE");
				lcd_putstring(1,0,"AUTHENTICATING");
				delay(10000);
			
				FACE_VERIFYING_1();
				//cash_handling_finger();
				delay(5000);
				break;

		case 3:lcd_clear();
			   	lcd_putstring(0,0,"USER3 ");
				delay(10000);
				z=0;
				lcd_clear();
			   	lcd_putstring(0,0,"WAIT FACE");
				lcd_putstring(1,0,"AUTHENTICATING");
				delay(10000);
				FACE_VERIFYING_2();
				//cash_handling_finger();
				delay(5000);
				break;
	
		case 4:lcd_clear();
			   	lcd_putstring(0,0,"USER4 ");
				delay(10000);
				z=0;
				lcd_clear();
			   	lcd_clear();
			   	lcd_putstring(0,0,"WAIT FACE");
				lcd_putstring(1,0,"AUTHENTICATING");
				delay(10000);
				FACE_VERIFYING_3();
				//cash_handling_finger();
				delay(5000);
				break;
		
		case 0:lcd_clear();
			   	lcd_putstring(0,0,"NOT VALID ");
				z=0;
				//delay(5000);
		        break;
		
												   
	  }
	 delay(10000);
	}


}
void FACE_VERIFYING(void)
{
	unsigned char ch1;
	soft_uart_init();
//	 SOFT_UART_tstring("FACE");
	 ch1 = SOFT_UART_recieve();
	 switch(ch1)
	 {
	  		case 'A':lcd_clear();
			 			lcd_putstring(0,0,"VALID PERSON");
			   	     lcd_putstring(1,0,"USER1 ");
					delay(10000);
					intWIFI();
	 				WIFI_UPLOAD_1();
					 break;
		    
			case 'B':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
					 
			case 'C':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
			case 'U':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
	  }
}
void FACE_VERIFYING_1(void)
{
	unsigned char ch1;
	soft_uart_init();
//	 SOFT_UART1_tstring("FACE");
	 ch1 = SOFT_UART_recieve();
	 switch(ch1)
	 {
	  		case 'A':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
		    
			case 'B':lcd_clear();
			    		lcd_putstring(0,0,"VALID PERSON");
			   	     lcd_putstring(1,0,"USER2 ");
					delay(10000);
						intWIFI();
	 				WIFI_UPLOAD_2();
					 break;
					 
			case 'C':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
			case 'U':lcd_clear();
			    		lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
	  }
}
void FACE_VERIFYING_2(void)
{
	unsigned char ch1;
	soft_uart_init();
	// SOFT_UART_tstring("FACE");
	 ch1 = SOFT_UART_recieve();
	 switch(ch1)
	 {
	  		case 'A':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
		    
			case 'B':lcd_clear();
			    		lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
					 
			case 'C':lcd_clear();
			    		lcd_putstring(0,0,"VALID PERSON");
			   	     lcd_putstring(1,0,"USER3 ");
					delay(10000);
						intWIFI();
	 				WIFI_UPLOAD_3();
					 break;
			case 'U':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
	  }
}
void FACE_VERIFYING_3(void)
{
	unsigned char ch1;
	soft_uart_init();
	// SOFT_UART_tstring("FACE");
	 ch1 = SOFT_UART_recieve();
	 switch(ch1)
	 {
	  		case 'A':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
		    
			case 'B':lcd_clear();
			    	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 				main();
					 break;
					 
			case 'C':lcd_clear();
					 	lcd_putstring(0,0,"NOT VALID ");
					delay(10000);
	 					main();
					 break;
			case 'D':lcd_clear();
			    		lcd_putstring(0,0,"VALID PERSON");
			   	     lcd_putstring(1,0,"USER4 ");
					delay(10000);
						intWIFI();
	 				WIFI_UPLOAD_4();
					 break;
	  }
}

int FINGER_SCAN(void)
{	
      int k = 0,id = 0;
	  unsigned char USER_ID_BUFF[10];
	
//	IO0CLR |= SELECT_LINE_A;  
    
	lcd_command_write(1);
	lcd_command_write(0x80);
	putSLcd("PLACE YOUR");
	lcd_command_write(0xc0);
	putSLcd("FINGER");
	delay(100);

	  j=0;
	  for(k=0;k<=4;k++)
	  {
		  j=0;
		  while(j<16)
		  uart0_putc(a[j++]);
		  delay(500);	  
	 }
	 
	 j=0;
	 while(j<12)
	 uart0_putc(a1[j++]);
	 delay(500);

  	UART0Buffer[9] = 0xff;

		while(UART0Buffer[9] != 0x00)
		{
			j=0;
			while(j<12)
			uart0_putc(a2[j++]);
			if (UART0Count != 0)
			{
			    U0IER = IER_THRE | IER_RLS;					
			    UART0Count = 0;
			    U0IER = IER_THRE | IER_RLS | IER_RBR;	
			}
				delay(4000);	
		   
		}
		
		lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("SEARCHING");
		lcd_command_write(0xc0);
		putSLcd("IMAGE .");
		delay(2000);
		putSLcd(" .");
		delay(2000);
		putSLcd(" .");
		delay(2000);
		putSLcd(" .");	
		
		j=0;
		while(j<13)
		uart0_putc(a3[j++]);
		
		lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("FINDING");
		lcd_command_write(0xc0);
		putSLcd("IMAGE .");
		delay(2000);
		putSLcd(" .");
		delay(2000);
		putSLcd(" .");
		delay(2000);
		putSLcd(" .");
	
		j=0;
		UART0Buffer[9] = 0xff;
		 
		if (UART0Count != 0)
		{
			  U0IER = IER_THRE | IER_RLS;					
			  UART0Count = 0;
			  U0IER = IER_THRE | IER_RLS | IER_RBR;	
		}

		while(j<17)
		uart0_putc(a4[j++]); 
		delay(1000);

		if (UART0Count != 0)
		{
			  U0IER = IER_THRE | IER_RLS;					
			  UART0Count = 0;
			  U0IER = IER_THRE | IER_RLS | IER_RBR;	
		}

		if(UART0Buffer[9] == 0x00)
		{
			id = UART0Buffer[11];
			sprintf(USER_ID_BUFF,"%d",id);
		  	
			lcd_command_write(1);
			lcd_command_write(0x80);
			putSLcd("VALID USER");
			lcd_command_write(0xc0);
			putSLcd("USER ID: ");
			putSLcd(USER_ID_BUFF);
			delay(10000);
		//	IO0SET |= SELECT_LINE_A;
			return(id);	
		}
		else if(UART0Buffer[9] == 0x09)
		{	 
		  	lcd_command_write(1);
			lcd_command_write(0x80);
			putSLcd("USER NOT REG");
			lcd_command_write(0xc0);
			putSLcd("SORRY :(");			
			delay(3000);
			id=0;
		//	IO0SET |= SELECT_LINE_A;
			return(id);
		}
		else if(UART0Buffer[9] == 0x01)
		{
		  	lcd_command_write(1);
			lcd_command_write(0x80);
			putSLcd("ERROR WIPE YOUR");
			lcd_command_write(0xc0);
			putSLcd("FINGER AND RETRY");			
			delay(30000);
		//	IO0SET |= SELECT_LINE_A;	
			return(0);	
		}
}
void FINGER_ENROL(void)
{
	int k=0;
		
		
	//	IO0CLR |= SELECT_LINE_A;  

  	UART0Buffer[9] = 0xff;

	 for(k=0;k<=4;k++)
	 {
		 j=0;
		 while(j<16)
		 uart0_putc(a[j++]);
		 delay(500);	  
	 } 
	 	
	j=0;
	while(j<12)
	uart0_putc(a1[j++]);
	delay(500);

  		UART0Buffer[9] = 0xff;

		lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("PLACE YOUR");
		lcd_command_write(0xc0);
		putSLcd("FINGER");
		delay(5000);	
		while(UART0Buffer[9] != 0x00)
		{
			j=0;
			while(j<12)											   
			uart0_putc(a2[j++]);
			if (UART0Count != 0)
			{
			    U0IER = IER_THRE | IER_RLS;					
			    UART0Count = 0;
			    U0IER = IER_THRE | IER_RLS | IER_RBR;	
			}
				delay(8000);	
		   
		}
				
		j=0;
		while(j<13)
		uart0_putc(a3[j++]);
		delay(5000);

		lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("PLACE YOUR FINGER");
		lcd_command_write(0xc0);
		putSLcd("FOR CONFIRMATION");
		delay(5000);

		UART0Buffer[9] = 0xff;
		while(UART0Buffer[9] != 0x00)
		{
			j=0;
			while(j<12)											   
			uart0_putc(a2[j++]);
			if (UART0Count != 0)
			{
			    U0IER = IER_THRE | IER_RLS;					
			    UART0Count = 0;
			    U0IER = IER_THRE | IER_RLS | IER_RBR;	
			}
				delay(8000);	
		   
		}

		lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("WAIT ALLOCATING");
		lcd_command_write(0xc0);
		putSLcd("USER ID...");
		delay(5000);
	
		j=0;
		UART0Buffer[9] = 0xff;
	
		while(j<13)
		uart0_putc(a5[j++]); 
		delay(5000);
		
		j=0;
		while(j<9)
		uart0_putc(a1[j++]);
		
		uart0_putc(0x05);
		uart0_putc(0x00);
		uart0_putc(0x09); 
		delay(5000);
	
		j=0;
		while(j<12)
		uart0_putc(a6[j++]);
		
		uart0_putc(c);
		uart0_putc(0x00);
		uart0_putc(0x0f + c); 
		delay(5000);
		
		c++;

	    lcd_command_write(1);
		lcd_command_write(0x80);
		putSLcd("YOU ARE REGISTERED ");
		lcd_command_write(0xc0);
		putSLcd("THANKING YOU :)");
		delay(5000);
	//	IO0SET |= SELECT_LINE_A;
}
