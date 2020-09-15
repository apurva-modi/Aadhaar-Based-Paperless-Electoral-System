#include <LPC21xx.H> 
#include <stdio.h>             
#include "Serial.h"
#include "wifi.h"
#include "string.h"
#include "delay.h"
#include "lcd.h"

//***************SERIAL PORT FUNCTIONS****************************************************


#define WIFIPutSSerial(string) uart1_puts( string )
#define WIFIGetCSerial( )  uart1_getkey()
#define WIFIPutCSerial(chr) uart1_putc(chr)
unsigned char WIFI_D[20];



unsigned char balance_buff[50];
void putSLcd(unsigned char *st) 
{
	for( ;*st ;lcd_putchar(*st++) );
}
 void delay_1(int l)
{
  int j=0,i=0;

  for(j=0;j<l;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<1275;i++);
  }
}

/**
********************************************************************************************
	Function Name : intGsm()
**********************************************************************************************
*/
void recvResponse(unsigned char *response)
{
    unsigned char ch;
    
  	while(WIFIGetCSerial() != '\n' );
    while( (ch = WIFIGetCSerial()) != '\r' )*response++ = ch;
	*response = '\0' ;       
}

void WIFI_CONNECT_Response(unsigned char *response)
{
    unsigned char ch;
    
//  while(WIFIGetCSerial() != '\r' );
	while(WIFIGetCSerial() != '\n' );
    while( (ch = WIFIGetCSerial()) != '\r' )*response++ = ch; 
	*response = '\0' ;       
}
void WIFI_RECEIVE_IP(unsigned char *response)
{
    unsigned char ch;
    
//  while(WIFIGetCSerial() != '\r' );
	while(WIFIGetCSerial() != '"' );
    while( (ch = WIFIGetCSerial()) != '"' )*response++ = ch; 
	*response = '\0' ;       
}
void Receive_Data(unsigned char *response)
{
    unsigned char ch,i=0;
    
  	while(WIFIGetCSerial() != ':' );
    while( (ch = WIFIGetCSerial()) != '$' )WIFI_D[i++] = ch;
	WIFI_D[i] = '\0' ; 
	      
}
void intWIFI( void )
{
	unsigned char buff[]=0;
	WIFIPutCSerial('A');
	delay_1(1000);
	WIFIPutCSerial('T');
	delay_1(1000);
	WIFIPutCSerial('E');
	delay_1(1000);
	WIFIPutCSerial('0');
	delay_1(1000);
	WIFIPutSSerial("\r\n");
	recvResponse(buff);
	delay_1(1000);
	lcd_command_write(1);
	lcd_command_write(0x80);
	lcd_putstring(1,0,"CONNECTING.");	
	delay_1(10000);
	delay_1(1000);
	WIFIPutSSerial("AT\r\n"); 	  
	recvResponse(buff);
	
	lcd_command_write(0x80);
	lcd_putstring(1,0,"CONNECTING..");
	delay_1(5000);
	
	WIFIPutSSerial("AT+CWMODE=1\r\n"); // MULTIPLE MODE SELECTION    
	recvResponse(buff);
	lcd_command_write(0x80);

	lcd_putstring(1,0,"CONNECTING...");
	delay_1(5000);
	
	WIFIPutSSerial("AT+CWJAP=\"OFFICE\",\"p$bfly96\"\r\n"); // MULTIPLE MODE SELECTION 
	delay_1(50000); 
	WIFIPutSSerial("AT+CIPMUX=0\r\n"); // SINGLE MODE SELECTION    
	recvResponse(buff);
	lcd_command_write(0x80);
	lcd_putstring(0,0,"CONNECTING TO ");
	lcd_putstring(1,0,"SERVER...... ");
	delay_1(50000); 




}

void WIFI_UPLOAD_1(void)
{
	lcd_command_write(1);       
    lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT.....");
	delay_1(20000);
	WIFIPutSSerial("AT+CIPSTART=\"TCP\",\"139.59.92.200\",1000\r\n");
	delay_1(50000);
	WIFIPutSSerial("AT+CIPSEND=9\r\n"); // MULTIPLE MODE SELECTION 
	 delay_1(50000);
	WIFIPutSSerial("/Voting/a");
//	WIFIPutSSerial(st);
	WIFIPutSSerial("\r\n");
	delay_1(50000);
	lcd_command_write(0x01);
 	lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT SENDING INFO.....");		
	delay_1(10000);

 }
void WIFI_UPLOAD_2(void)
{
	lcd_command_write(1);       
    lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT.....");
	delay(20000);
	WIFIPutSSerial("AT+CIPSTART=\"TCP\",\"139.59.92.200\",1000\r\n");
	delay_1(50000);
	WIFIPutSSerial("AT+CIPSEND=9\r\n"); // MULTIPLE MODE SELECTION 
	  	delay_1(50000);
	WIFIPutSSerial("Voting/b");
//	WIFIPutSSerial(st);
	WIFIPutSSerial("\r\n");
	delay_1(50000);
	lcd_command_write(0x01);
 	lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT SENDING INFO.....");		
	delay_1(10000);

 }
 void WIFI_UPLOAD_3(void)
{
	lcd_command_write(1);       
    lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT.....");
	delay(5000);
	WIFIPutSSerial("AT+CIPSTART=\"TCP\",\"139.59.92.200\",1000\r\n");
	delay_1(50000);
	WIFIPutSSerial("AT+CIPSEND=11\r\n"); // MULTIPLE MODE SELECTION 
	delay_1(5000);
	WIFIPutSSerial("/Voting/c");
		WIFIPutSSerial("\r\n");
	delay_1(5000);
	lcd_command_write(0x01);
 	lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT SENDING INFO.....");		
	delay_1(5000);
//	WIFIPutSSerial(st);



 }
 void WIFI_UPLOAD_4(void)
{
	lcd_command_write(1);       
    lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT.....");
	delay(20000);
	WIFIPutSSerial("AT+CIPSTART=\"TCP\",\"139.59.92.200\",1000\r\n");
	delay_1(50000);
	WIFIPutSSerial("AT+CIPSEND=9\r\n"); // MULTIPLE MODE SELECTION 
	 delay_1(50000);
	WIFIPutSSerial("/Voting/d");
//	WIFIPutSSerial(st);
	WIFIPutSSerial("\r\n");
	delay_1(50000);
	lcd_command_write(0x01);
 	lcd_putstring(0,0,"CONNECTED SERVER");
	lcd_putstring(1,0,"WAIT SENDING INFO.....");		
	delay_1(10000);

 }