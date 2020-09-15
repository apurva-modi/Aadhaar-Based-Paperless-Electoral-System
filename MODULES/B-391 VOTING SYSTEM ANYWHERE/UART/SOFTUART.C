#include <LPC214X.H>

#include "SOFTUART.h"
//#define	desired_baud_rate	9600
//
//#define fosc	15000000
//#define	baud_rate	((fosc/desired_baud_rate)*(1/fosc))
#define	TX	(1<<24)	
#define	RX	(1<<25)

//#define baud_rate	833	//br 1200
#define baud_rate	104	//br 9600

unsigned char transmit[20];
unsigned char recieve;


void soft_uart_init();
void timer1delay(unsigned int b);
void SOFT_UART_tstring(unsigned char *buff1);
void SOFT_UART_transmit(unsigned char buff);
unsigned char SOFT_UART_recieve(void);

void soft_uart_init()
{
	IO1DIR	|=	TX;		  			//OUTPUT
	IO1DIR	&=~	RX;					//INPUT

	IO1SET	|=	TX;
	//timer1delay(baud_rate);
}


void SOFT_UART_tstring(unsigned char *buff1)
{
	while(*buff1)
	{
		SOFT_UART_transmit(*buff1++);		
	}

}

void SOFT_UART_transmit(unsigned char buff)
{
	unsigned char i = 0;
	IO1CLR	|=	TX;
	timer1delay(baud_rate);

	for(i=0;i<8;i++)
	{
		if(((buff >>i)	&	0x01)==0x01)
		{
			IO1SET	|=	TX;	
		}
		else
		{
			IO1CLR	|=	TX;	
		}
		timer1delay(baud_rate);
	}
	IO1SET	|=	TX;
	timer1delay(baud_rate);
}

unsigned char SOFT_UART_recieve(void)
{
	unsigned char i=0;
	unsigned char Datavalue=0;
	while(IO1PIN & RX);
	timer1delay(baud_rate);
	timer1delay(baud_rate/2);

	for(i=0;i<8;i++)
	{
		if(IO1PIN & RX)
		{
			Datavalue =Datavalue + (1<<i);
		}
		timer1delay(baud_rate);
	}
	if(IO1PIN & RX)
	{
		timer1delay(baud_rate);
		return Datavalue;
	}	
	else
	{
		timer1delay(baud_rate);
		return 0x00;
	}
}



void timer1delay(unsigned int b)   //1us
{	
	T1TC=T1PC=0;
	T1CTCR=0x0000;
	T1PR=14;
	T1MR0=b;
	T1MCR=0x00000004;
	T1TCR=0x02;
	T1TCR=0x01;
	while(T1TC!=T1MR0);
	T1TC=0;
}