#include <LPC21xx.H> 
#include <stdio.h>             
#include "Serial.h"
#include "gsm.h"
#include "string.h"
#include "delay.h"
#include "lcd.h"

//***************SERIAL PORT FUNCTIONS****************************************************

#define GsmPutSSerial(string) uart0_puts( string )
#define GsmGetCSerial( )  uart0_getkey()
#define GsmPutCSerial(chr) uart0_putc(chr)

//****************************************************************************************
//#define  getCSerial() uart0_getkey() 

void recvResponse(unsigned char *response)
{
    unsigned char ch;
    while(GsmGetCSerial() != '\n' );
    while( (ch = GsmGetCSerial()) != '\r' ) *response++ = ch;
    *response = '\0' ; 
    GsmGetCSerial();
       
}
/**
********************************************************************************************
	Function Name : intGsm()
**********************************************************************************************
*/
void intGsm( void )
{
     unsigned char buff[10];  
    //*******Echo OFF**************************
    GsmPutCSerial('A'); 
    delay(100);
    GsmPutCSerial('T'); 
    delay(100);
    GsmPutCSerial('E');
    delay(100);
    GsmPutCSerial('0');
    delay(100);
    GsmPutCSerial('\r'); 
	
    recvResponse(buff);

    //*****************************************
    GsmPutSSerial("AT+CMGF=1\r"); //Initialize GSM For mobile 
    recvResponse(buff);   
    
    GsmPutSSerial("AT+CNMI=0,0,0,0\r"); //Disabling unsolicited sms indication.
    recvResponse(buff);
    
    GsmPutSSerial("AT+CSAS\r"); //Save the SMS Settings 
    recvResponse(buff); 
}
/**
********************************************************************************************
	Function Name :	sendSMS()
**********************************************************************************************
*/


unsigned char sendSMS( unsigned char *num, unsigned char * str )
{
  
     unsigned char ch;
     unsigned char res[10];
     unsigned char *response = res;
   	GsmPutSSerial("AT+CMGS=\"");
	GsmPutSSerial(num);
	GsmPutSSerial("\"\r");
	
   while( (ch = GsmGetCSerial()) != '>' && ch !='+' ) ;
   if( ch == '+' )
    {
        //Here means some error is thier so get error and return false
        *response++ = ch;
        while( (ch = GsmGetCSerial()) != '\r' ) *response++ = ch;
        *response = '\0' ; 
        GsmGetCSerial();
        return 0;
    }
   	GsmGetCSerial(); 
   	GsmPutSSerial( str );		
   	GsmPutCSerial(26);	   //Send Control Z.    
    recvResponse( response );

    if( response[3] != 'S' )
    {              
        recvResponse( response );
       return 1;
    }
    
    return 0 ;      
}
/**
********************************************************************************************
	Function Name :	getSMS()
**********************************************************************************************
*/

unsigned char getSMS(sms_data *sms_data_ptr)
{
     unsigned char ch, i;
	  
    GsmPutSSerial("AT+CMGL=\"ALL\"\r");
    
    while( (ch = GsmGetCSerial()) != 'K' && ch != '+' ) ;
    if( ch == 'K' )
    {
        while( GsmGetCSerial() != '\r' );
        while( GsmGetCSerial() != '\n' );  
        return 0; 
    }
    
    while( (ch = GsmGetCSerial()) != 'S' && ch != 'G' ) ;
    
    if( ch == 'S' )
    {
        while( GsmGetCSerial() != '\r' );
        while( GsmGetCSerial() != '\n' );  
        return 0; 
    }
    
    while( GsmGetCSerial() != ' ' );
     //**********************Get the Index******************************
    i = 0 ;
    while( (ch = GsmGetCSerial()) != ',' ) sms_data_ptr->index[i++] = ch;
    sms_data_ptr->index[i++] = '\0';
    //************************************************************************
    
    while( GsmGetCSerial() != ',' );
    while( GsmGetCSerial() != '\"' );
    
    //**********************Get the Phone number******************************
    i = 0 ;
    while( (ch = GsmGetCSerial()) != '\"' ) sms_data_ptr->phone_num[i++] = ch;
    sms_data_ptr->phone_num[i++] = '\0';
    //************************************************************************
    
    while( GsmGetCSerial() != '\n' );
    
    //**********************Get the Data******************************
    i = 0 ;
    while( (ch = GsmGetCSerial()) != '\r' ) sms_data_ptr->dat[i++] = ch;
    sms_data_ptr->dat[i++] = '\0';
    //************************************************************************
    
     while( GsmGetCSerial() != '\n' );
    
    //------------Now all the data has be read need to wait for OK-------
    
    while(1)
    {
        if( GsmGetCSerial() == '+' )
        {
            while( GsmGetCSerial() != '\n' );
            while( GsmGetCSerial() != '\r' );
            while( GsmGetCSerial() != '\n' ); 
        }
        else
        {
            while( GsmGetCSerial() != '\n' );
            while( GsmGetCSerial() != '\n' ); 
            return 1;  
        }
    }          
} 

/********************************************************************************************
	Function Name :	deleteSms()
**********************************************************************************************
*/
unsigned char deleteSms(unsigned char *index)
{
    unsigned char response[10]; 
    GsmPutSSerial("AT+CMGD="); 
    GsmPutSSerial(index);  
    GsmPutSSerial("\r"); 
    recvResponse( response );  
    return 1;  
}

//void recivecontr(void)
//{
// 	if( getSMS(&sms_dat) )      
//	{ 
//	    lcd_clear();	
//		putSLcd(sms_dat.dat);
//		putSLcd(sms_dat.phone_num);
//		delay(3000);
//		sms_dat.dat[4] = '\0';
//  
//	}
//	deleteSms(sms_dat.index);
//	delay(20000);
//	lcd_clear();		
//}












