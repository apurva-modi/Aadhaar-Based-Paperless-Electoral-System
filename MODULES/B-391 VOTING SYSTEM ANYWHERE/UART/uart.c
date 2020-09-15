/*****************************************************************************
 *   uart.c:  UART API file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "LPC214x.H"                        /* LPC21xx definitions */
#include "type.h"
#include "target.h"
#include "irq.h"
#include "uart.h"

DWORD UART0Status;
BYTE UART0TxEmpty = 1;
BYTE UART0Buffer[BUFSIZE];
DWORD UART0Count = 0;

DWORD UART1Status;
BYTE UART1TxEmpty = 1;
BYTE UART1Buffer[BUFSIZE];
DWORD UART1Count = 0;


/*****************************************************************************
** Function name:		UART0Handler
**
** Descriptions:		UART0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART0Handler (void) __irq 
{
    BYTE IIRValue, LSRValue;
    BYTE Dummy;

    IENABLE;				/* handles nested interrupt */	
    IIRValue = U0IIR;
    
    IIRValue >>= 1;			/* skip pending bit in IIR */
    IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
    if ( IIRValue == IIR_RLS )		/* Receive Line Status */
    {
	LSRValue = U0LSR;
	/* Receive Line Status */
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
	    /* There are errors or break interrupt */
	    /* Read LSR will clear the interrupt */
	    UART0Status = LSRValue;
	    Dummy = U0RBR;		/* Dummy read on RX to clear 
					interrupt, then bail out */
	    IDISABLE;
	    VICVectAddr = 0;		/* Acknowledge Interrupt */
	    return;
	}
	if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
	{
	    /* If no error on RLS, normal ready, save into the data buffer. */
	    /* Note: read RBR will clear the interrupt */
	    UART0Buffer[UART0Count] = U0RBR;
	    UART0Count++;
	    if ( UART0Count == BUFSIZE )
	    {
		UART0Count = 0;		/* buffer overflow */
	    }	
	}
    }
    else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
	/* Receive Data Available */
	UART0Buffer[UART0Count] = U0RBR;
	UART0Count++;
	if ( UART0Count == BUFSIZE )
	{
	    UART0Count = 0;		/* buffer overflow */
	}
    }
    else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
    {
	/* Character Time-out indicator */
	UART0Status |= 0x100;		/* Bit 9 as the CTI error */
    }
    else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
    {
	/* THRE interrupt */
	LSRValue = U0LSR;		/* Check status in the LSR to see if
					valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	    UART0TxEmpty = 1;
	}
	else
	{
	    UART0TxEmpty = 0;
	}
    }
    
    IDISABLE;
    VICVectAddr = 0;		/* Acknowledge Interrupt */
}

/*****************************************************************************
** Function name:		UART1Handler
**
** Descriptions:		UART1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void UART1Handler (void) __irq 
{
    BYTE IIRValue, LSRValue;
    BYTE Dummy;

    IENABLE;				/* handles nested interrupt */	
    IIRValue = U1IIR;
    
    IIRValue >>= 1;			/* skip pending bit in IIR */
    IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
    if ( IIRValue == IIR_RLS )		/* Receive Line Status */
    {
	LSRValue = U1LSR;
	/* Receive Line Status */
	if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
	    /* There are errors or break interrupt */
	    /* Read LSR will clear the interrupt */
	    UART1Status = LSRValue;
	    Dummy = U1RBR;		/* Dummy read on RX to clear 
					interrupt, then bail out */
	    IDISABLE;
	    VICVectAddr = 0;		/* Acknowledge Interrupt */
	    return;
	}
	if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
	{
	    /* If no error on RLS, normal ready, save into the data buffer. */
	    /* Note: read RBR will clear the interrupt */
	    UART1Buffer[UART1Count] = U1RBR;
	    UART1Count++;
	    if (UART1Count == BUFSIZE)
	    {
		UART1Count = 0;		/* buffer overflow */
	    }	
	}
    }
    else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
	/* Receive Data Available */
	UART1Buffer[UART1Count] = U1RBR;
	UART1Count++;
	if (UART1Count == BUFSIZE)
	{
	    UART1Count = 0;		/* buffer overflow */
	}
    }
    else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
    {
	/* Character Time-out indicator */
	UART1Status |= 0x100;		/* Bit 9 as the CTI error */
    }
    else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
    {
	/* THRE interrupt */
	LSRValue = U1LSR;		/* Check status in the LSR to see if
					valid data in U0THR or not */
	if ( LSRValue & LSR_THRE )
	{
	    UART1TxEmpty = 1;
	}
	else
	{
	    UART1TxEmpty = 0;
	}
    }
    
    IDISABLE;
    VICVectAddr = 0;		/* Acknowledge Interrupt */
}

/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART0 port, setup pin select,
**				clock, parity, stop bits, FIFO, etc.
**
** parameters:			UART baudrate
** Returned value:		true or false, return false only if the 
**				interrupt handler can't be installed to the 
**				VIC table
** 
*****************************************************************************/
DWORD UARTInit(BYTE uart_num, DWORD baud )
{
	
	switch(uart_num)
	{
	    case UART0:
			PINSEL0 &= ~(0x0000000F);       /* Enable RxD0 and TxD0 function 01*/
			PINSEL0 |= 0x00000005;
		    U0LCR = 0x83;               /* 8 bits, no Parity, 1 Stop bit    */
        	U0DLL = baud;
			U0DLM = (baud >> 8);
			 
		    U0LCR = 0x03;               /* DLAB = 0                         */
		    U0FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

		    if ( install_irq( UART0_INT, (void *)UART0Handler ) == FALSE )
		    {
			return (FALSE);
		    }
		   
		    U0IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART0 interrupt */
			break;

		case UART1:
			PINSEL0 &= ~(0x000F0000);       /* Enable RxD1 and TxD1 function 01*/
			PINSEL0 |= 0x00050000;
		    U1LCR = 0x83;               /* 8 bits, no Parity, 1 Stop bit    */
			U1DLL = baud;
			U1DLM = (baud >> 8);
		  	 
		    U1LCR = 0x03;               /* DLAB = 0                         */
		    U1FCR = 0x07;		/* Enable and reset TX and RX FIFO. */

		    if (install_irq(UART1_INT, (void *)UART1Handler ) == FALSE)
		    {
			return (FALSE);
		    }
		   
		    U1IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART1 interrupt */
			break;
			
	}

    return (TRUE);
}

/*****************************************************************************
** Function name:		UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**				on the data length
**
** parameters:			buffer pointer, and data length
** Returned value:		None
** 
*****************************************************************************/
void UARTSend(BYTE uart_num, BYTE *BufferPtr, DWORD Length )
{
	switch(uart_num)
	{
		case UART0:		
			while (Length != 0)
		    {
				while (!(UART0TxEmpty & 0x01));	/* THRE status, contain valid 
									data */
				U0THR = *BufferPtr;
				UART0TxEmpty = 0;	/* not empty in the THR until it shifts out */
				BufferPtr++;
				Length--;
		    }
			break;

		case UART1:
			while (Length != 0)
		    {
				while (!(UART1TxEmpty & 0x01));	/* THRE status, contain valid 
									data */
				U1THR = *BufferPtr;
				UART1TxEmpty = 0;	/* not empty in the THR until it shifts out */
				BufferPtr++;
				Length--;
		    }
			break;
		}			
}

/******************************************************************************
**                            End Of File
******************************************************************************/
