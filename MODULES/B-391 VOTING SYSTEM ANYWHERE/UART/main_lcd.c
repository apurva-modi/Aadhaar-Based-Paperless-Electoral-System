#include <LPC21xx.H>   	   /* LPC214x definitions */
#include "lcd_arm.h"


#define LCD_BACK_LIGHT_TIMEOUT 1000



#define LCD_DATA_DIR	   IO0DIR
#define LCD_DATA_SET	   IO0SET
#define LCD_DATA_CLR	   IO0CLR

#define LCD_CTRL_DIR	   IO0DIR
#define LCD_CTRL_SET       IO0SET
#define LCD_CTRL_CLR       IO0CLR

#define LCDRS	           (1 << 15)
#define LCDRW	           (1 << 16)
#define LCDEN	           (1 << 17)

#define LCD_D4 (1 << 18)
#define LCD_D5 (1 << 19)
#define LCD_D6 (1 << 20)
#define LCD_D7 (1 << 21)




#define LCD_DATA_MASK           (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)
#define LCD_BUSY_FLAG           LCD_D7

#define LCD_IO0PIN				IO0PIN
#define MAX_CHAR_IN_ONE_LINE 16
enum ROW_NUMBERS
{

  LINE1,
  LINE2	
};

//void delay(int count);
//void lcd_command_write( unsigned char command );   
//void set_lcd_port_output( void );
// 
//void lcd_data_write( unsigned char data );  
//void init_lcd( void );    
//void lcd_putstring( unsigned char line,unsigned char pos, char *string ); 
//int lcd_gotoxy( unsigned int x, unsigned int y); 
//void lcd_putchar( int c );   
//void test_cmd(void);  


/**
**************************************************************************

****1111
  Function Name : delay()

  Description :This function suspends the tasks for specified ticks.	

  Input :  ticks:no of ticks in multiple of 1 usec
            task: task to be suspended

  Output : void

  Note :
*******************************************************************************
*/

 /*int main(void)
 {
  	init_lcd();
//	test_cmd();
//	lcd_data_write('E');
	IO1DIR &=~ (KEYS);
	IO1CLR |= KEYS;
	
	//lcd_putstring(0,0,"Selecet Ur order");
	main_menu();
	while(1);
 } */
 
void delay_lcd(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<1275;i++);
  }
}
/**
********************************************************************************************
  Function Name :	wait_lcd()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void wait_lcd( void )
{
  LCD_DATA_DIR &= ~LCD_BUSY_FLAG;
  LCD_CTRL_CLR |=  LCDRS;	
  LCD_CTRL_SET |=  LCDRW |LCDEN;
  while(LCD_IO0PIN & LCD_BUSY_FLAG);		/* wait for busy flag to become low */
  
  LCD_CTRL_CLR |= LCDEN | LCDRW;
  LCD_DATA_DIR |= LCD_DATA_MASK;
  
  delay_lcd(100);  
}
/**
********************************************************************************************
  Function Name :	lcd_command_write()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_command_write( unsigned char command )
{
  unsigned char temp=0;
  unsigned int temp1=0;

  temp=command;
  temp=(temp>>4)&0x0F;
  temp1=(temp<<18)&LCD_DATA_MASK;

  LCD_CTRL_CLR |= LCDRS;
  LCD_CTRL_SET |= LCDEN;
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET |= temp1;
  delay_lcd(2);
  LCD_CTRL_CLR |= LCDEN;

  temp=command;
  temp&=0x0F;
  temp1=(temp<<18)&LCD_DATA_MASK;
  delay(2);

  LCD_CTRL_CLR |= LCDRS;
  LCD_CTRL_SET |= LCDEN;
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET |= temp1;
  delay_lcd(2);	
  LCD_CTRL_CLR |= LCDEN;
wait_lcd();
}
/**
********************************************************************************************
  Function Name :	set_lcd_port_output()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void set_lcd_port_output( void )
{
  LCD_CTRL_DIR |= ( LCDEN | LCDRS | LCDRW );
  LCD_CTRL_CLR |= ( LCDEN | LCDRS | LCDRW );	
  LCD_DATA_DIR |= LCD_DATA_MASK;
}
/* *
********************************************************************************************
  Function Name :	lcd_clear()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_clear( void)
{
  lcd_command_write( 0x01 );
}

/**
********************************************************************************************
  Function Name :	lcd_gotoxy()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/

int lcd_gotoxy( unsigned int x, unsigned int y)
{
  int retval = 0;
  
  if( (x > 1) && (y > 15) )
  {
    retval = -1;
  } else {
  if( x == 0 ) 
  {
   lcd_command_write( 0x80 + y );		/* command - position cursor at 0x00 (0x80 + 0x00 ) */
  } else if( x==1 ){
    lcd_command_write( 0xC0 + y );		/* command - position cursor at 0x40 (0x80 + 0x00 ) */
    }
  }
   return retval;
} 

/**
********************************************************************************************
  Function Name :	lcd_data_write()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_data_write( unsigned char data )
{
  unsigned char temp=0;
  unsigned int temp1=0;

  temp=data;
  temp=(temp>>4)&0x0F;
  temp1=(temp<<18)&LCD_DATA_MASK;

  LCD_CTRL_SET |= LCDEN|LCDRS;
  LCD_DATA_CLR = LCD_DATA_MASK;
  LCD_DATA_SET = temp1;
  delay_lcd(2);
  LCD_CTRL_CLR |= LCDEN;

  temp=data;
  temp&=0x0F;
  temp1=(temp<<18)&LCD_DATA_MASK;

  LCD_CTRL_SET |= LCDEN|LCDRS;
  LCD_DATA_CLR = LCD_DATA_MASK;
  LCD_DATA_SET = temp1;
  delay_lcd(2);
  LCD_CTRL_CLR |= LCDEN; 
  wait_lcd();
}
/**
********************************************************************************************
  Function Name :	lcd_putchar()
  
  Description   
  :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_putchar( int c )
{
  lcd_data_write( c );
}

/**
********************************************************************************************
  Function Name :	lcd_putstring()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_putstring( unsigned char line,unsigned char pos, char *string )
{																				
  unsigned char len = MAX_CHAR_IN_ONE_LINE;

  lcd_gotoxy( line,pos);
  while(*string != '\0' && len--)
  {
    lcd_putchar( *string );
    string++;
  }
} 

/**
********************************************************************************************
  Function Name :	lcd_backlight_on()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/


/**
********************************************************************************************
 Function Name : turn_off_lcd_back_light()

 Description   :	

 Input         :	

 Output        : Void

 Note          :
********************************************************************************************
*/


/**
********************************************************************************************
  Function Name :	init_lcd()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void init_lcd( void )
{
  set_lcd_port_output();
  delay(100);
  lcd_command_write(0x28);     /*   4-bit interface, two line, 5X7 dots.        */
  lcd_command_write(0x02);     /*   cursor home                                 */
  lcd_command_write(0x06);     /*   Entry mode                       */
  lcd_command_write(0x0c) ;    /*   display on cursor blinking    */  
}

/**
********************************************************************************************
  Function Name :	test_cmd()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void test_cmd(void)
{
	lcd_command_write(0x38);   // Interface length 8-bit 2 line
	lcd_command_write(0x08);   //Display off,cursor off
	lcd_command_write(0x0C);   //Display on cursor off
	lcd_command_write(0x10);   //Move cursor left by 1 char
	lcd_command_write(0x14);   //Move cursor right by 1 char
	lcd_command_write(0x01);   //Clear display
}

/* *
********************************************************************************************
  Function Name :	lcd_clear()
  
  Description   :	
  										  d
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
//void lcd_clear( void)
//{
// lcd_command_write( 0x01 );
//}

		
