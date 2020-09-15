void delay_lcd(int count);
void lcd_command_write( unsigned char command );   
void set_lcd_port_output( void );
 
void lcd_data_write( unsigned char data );  
void init_lcd( void );    
void lcd_putstring( unsigned char line,unsigned char pos, char *string ); 
int lcd_gotoxy( unsigned int x, unsigned int y); 
void lcd_putchar( int c );   
void test_cmd(void);
void lcd_clear( void);

 