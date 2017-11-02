#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>

#define lcd_data		PORTA	//Define port A for LCD DB0-DB7
#define ddr_lcd_data	DDRA	//initialize Data direction register for PORTA 
#define lcd_control		PORTD	//Define Port D for LCD Control pins RS,RW,EN
#define ddr_lcd_control	DDRD	//initialize data direction register for PORTB
#define	RS				2
#define RW				7
#define EN				5

void check_busy(void);
void blink(void);
void send_command(unsigned char command);
void send_character(unsigned char character);
void send_string(char *stringOfCharacters);

int main(void)
{	
	ddr_lcd_control= 1 << RS|1 << RW|1 << EN;
	_delay_ms(15);
	
	send_command(0x01);	//clear screen command for lcd (0x01= 0000 0001)
	_delay_ms(2);	//delay for clearing screen
	send_command(0x38);	//set number of display line and font size (001D NF00) where D= display lines;0: 4 bit;1- 8 bit
	// N- number of display line 0: 1 line; 1: 2 line/F font size 0- 5x10; 1-5x7
	_delay_us(50);	// delay to set command
	send_command(0b00001111); // ( last 3 bits are significant; 1- display on;1- cursor/position on;1- cursor blinking on)
	\
	char position_no[3];
	
	while(1)
	{
		for(int x=0;x<85;x++)
		{
			send_command(0x80 + x);//1.set the current location
			send_string("");//2.put an x at that location
			itoa(x,position_no,10);		//3.display the location
			send_command(0x80 + 78);
			send_string(position_no);
			_delay_ms(50);//4.add a delay
			send_command(0x80 + x);//5.go back to the location
			send_string(" ");//6. put a space at the location
		}
	}
}


void check_busy(void)
{
	ddr_lcd_data= 0;	//initialize PORTA to read data
	lcd_control|= 1 << RW;	//enable Read
	lcd_control&= ~1 << RS;	//Register Select=0;
	while(lcd_data >= 0x80)		//check until the LCD data lines are set to 1000 0000 i.e 0x80 in HEx
	{
		blink();
	}
	ddr_lcd_data=0xFF;	//initialize PORTA to write data
}


void blink(void)
{
	lcd_control|= 1 << EN;	// Turn on the Enable
	asm volatile ("nop");	// wait statement in assembly
	asm volatile ("nop");
	lcd_control&= ~1 << EN;	// Turn off the Enable	
}

void send_command(unsigned char command)
{
	check_busy();	//check if lcd is busy
	lcd_data=command;	//send command to lcd
	lcd_control &= ~((1 << RW )| (1 << RS));	//Set lcd to command mode
	blink();	//delay for the lcd memory to write 
	lcd_data=0;	
}



void send_character(unsigned char character)
{
	check_busy();	//check if lcd is busy
	lcd_data=character;	//send command to lcd
	lcd_control &= ~(1 << RW );	//Set lcd to character mode
	lcd_control |= 1 << RS;			// "
	blink();	//delay for the lcd memory to write 
	lcd_data=0;	
}

void send_string(char *stringOfCharacters)
{
	while(*stringOfCharacters>0)
	{
	send_character(*stringOfCharacters++);
	}
}
