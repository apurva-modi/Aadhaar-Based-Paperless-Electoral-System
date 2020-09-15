#include <LPC21xx.H> 

void soft_uart_init();
void timer1delay(unsigned int b);
void SOFT_UART_tstring(unsigned char *buff1);
void SOFT_UART_transmit(unsigned char buff);
unsigned char SOFT_UART_recieve(void);

