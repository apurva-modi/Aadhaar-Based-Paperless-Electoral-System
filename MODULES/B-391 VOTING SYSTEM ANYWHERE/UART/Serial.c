#include <LPC21xx.H>                     /* LPC21xx definitions               */
#include "Serial.h"

#define CR     0x0D
unsigned char ch;
/* implementation of putchar (also used by printf function to output data)    */
int sendchar (int ch)  {                 /* Write character to Serial Port    */

  if (ch == '\n')  {
    while (!(U1LSR & 0x40));
    U1THR = CR;                          /* output CR */
  }
  while (!(U1LSR & 0x40));
  return (U1THR = ch);
}
int uart0_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U0LSR & 0x01));

  return (U0RBR);
//
//   if((U0LSR & 0x01))
//   		return (U0RBR);
//	else
//		 return 0;
}

int uart1_getkey (void)  {                     /* Read character from Serial Port   */

  while (!(U1LSR & 0x01));

  return (U1RBR);

//	if((U1LSR & 0x01)){
//		ch =  U1RBR;
//   		return 1;     //(U1RBR);
//		}
//	else
//		 return 0;
}

void uart1_init()
{
  /* initialize the serial interface   */
  PINSEL0 |= 0x00050000;           /* Enable RxD1 and TxD1                     */
  U1LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
 U1DLL = 97; 
// U1DLL = 195;                    /* 9600 Baud Rate @ 15MHz VPB Clock    97 , 4800=197    */
  U1LCR = 0x03;                   /* DLAB = 0                                 */
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART1-----------------------//
//------------------------------------------------------------------------------------------------//
void uart1_putc(char c)
{
	while(!(U1LSR & 0x40)); // Wait until UART1 ready to send character     
	U1THR = c;  // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart1_puts(char *p)
{
	while(*p) // Point to character
	{
		uart1_putc(*p++);   // Send character then point to next character
	}
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for Initial UART0 ----------------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_init()
{
  /* initialize the serial interface   */
  PINSEL0 |= 0x00000005;           /* Enable RxD0 and TxD0                     */
  U0LCR = 0x83;                   /* 8 bits, no Parity, 1 Stop bit            */
  U0DLL = 97;                     /* 9600 Baud Rate @ 15MHz VPB Clock         */
  U0LCR = 0x03;                   /* DLAB = 0                                 */
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send character 1 time via UART0-----------------------//
//------------------------------------------------------------------------------------------------//
void uart0_putc(char c)
{
	while(!(U0LSR & 0x40)); // Wait until UART0 ready to send character  
	U0THR = c; // Send character
}
//------------------------------------------------------------------------------------------------//
//---------------------------- Function for send string via UART1---------------------------------//
//------------------------------------------------------------------------------------------------//
void uart0_puts(char *p)
{
	while(*p) // Point to character
	{
		uart0_putc(*p++);  // Send character then point to next character
	}
}
