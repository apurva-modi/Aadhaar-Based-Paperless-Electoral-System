#ifndef _GSM
#define _GSM
#include "Serial.h"
#define SMS_DATA_LEN_MAX 170

typedef struct {
unsigned char index[3];
unsigned char phone_num[15] ;
unsigned char dat[SMS_DATA_LEN_MAX+1];

}sms_data;

//***************SERIAL PORT FUNCTIONS****************************************************

#define GsmPutSSerial(string) uart1_puts( string )
#define GsmGetCSerial( )  uart1_getkey()
#define GsmPutCSerial(chr) uart1_putc(chr)

//****************************************************************************************

extern void intGsm( void );
extern void recivecontr(void);
extern float convToFloat(  char *str ); 
extern unsigned char sendSMS(unsigned char *, unsigned char * );
extern void recvResponse(unsigned char * );
extern unsigned char getSMS(sms_data * );
extern unsigned char deleteSms(unsigned char * );
#endif 
