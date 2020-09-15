/*****************************************************************************
 *   uart.h:  Header file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __UART_H 
#define __UART_H

#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0x10

enum
{
  UART0,
  UART1	
};

DWORD UARTInit(BYTE uart_num, DWORD baudrate);
void UART0Handler( void ) __irq;
void UART1Handler( void ) __irq;
void UARTSend(BYTE uart_num, BYTE *BufferPtr, DWORD Length);

#define UART_BAUD(baud) (DWORD)((Fpclk / ((baud) * 16.0)) + 0.5)

#define B2400         UART_BAUD(2400)
#define B9600         UART_BAUD(9600)
#define B19200        UART_BAUD(19200)
#define B38400        UART_BAUD(38400)
#define B57600        UART_BAUD(57600)
#define B115200       UART_BAUD(115200)

#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
