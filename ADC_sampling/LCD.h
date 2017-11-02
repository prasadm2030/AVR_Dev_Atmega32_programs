#ifndef LCD
#define LCD

#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>

#define lcd_data		PORTA  
#define ddr_lcd_data	DDRA
#define lcd_control		PORTD
#define ddr_lcd_control	DDRD
#define EN				5	//ENABLE
#define RW				7	//READ/WRITE
#define RS				2	//REGISTER SELECT 0/1


void blink(void);
void check_busy(void);
void send_command(unsigned char command);
void send_character(unsigned char character);
void send_string(char *string);
void GotoLocation(uint8_t x, uint8_t y);
void Send_stringwithLocation(uint8_t x, uint8_t y, char *StringOfCharacters);
void Send_IntegerToLCD(uint8_t x, uint8_t y, int IntegerToDisplay, char NumberOfDigits);
void InitializeLCD(void);

char firstColumnPositions[4] = {0, 64, 20, 84};

void blink(void)				//refresh lcd sun-routine
{
	lcd_control|= 1 << EN;		//enable the lcd
	asm volatile("nop");		//wait
	asm volatile("nop");		//wait
	lcd_control&= ~1 << EN;	//disable lcd
}

void check_busy(void)		//check if lcd is performing any operation()sub-routine
{
	ddr_lcd_data=0;			//initialize the data lines as input 
	lcd_control|=1 << RW;	//read mode of lcd
	lcd_control&= ~1 << RS;	//command mode of lcd
	while(lcd_data >= 0x80);	// busy state
	{
		blink();
	}
	ddr_lcd_data= 0xFF;		//set back the data lines as output
}

void send_command(unsigned char command)	// send command sub-routine 
{
	check_busy();			//check if lcd is busy
	lcd_data=command;		//send the command
	lcd_control&= ~((1 << RW)|(1 << RS));	//set to write mode(RW=0), command mode(RS=0)
	blink();								//REFRESH
	lcd_data=0;								//set the data lines to 0
}

void send_character(unsigned char character)	//send character sub-routine
{
	check_busy();				//check if lcd is busy
	lcd_data=character;			//send the character on datalines
	lcd_control|= 1 << RS;		//set to character mode
	lcd_control&= ~(1 << RW);	//set to write mode
	blink();					//refresh
	lcd_data=0;					//set the data lines to 0
}

void send_string(char *string)
{
	while(*string>0)
	{
		send_character(*string++);
	}
}

void GotoLocation(uint8_t x, uint8_t y)
{
	send_command(0x80 + firstColumnPositions[y-1] + (x-1));
}

void Send_stringwithLocation(uint8_t x, uint8_t y, char *StringOfCharacters)
{
GotoLocation(x, y);
send_string(StringOfCharacters);
}

void Send_IntegerToLCD(uint8_t x, uint8_t y, int IntegerToDisplay, char NumberOfDigits)
{
char StringToDisplay[NumberOfDigits];
itoa(IntegerToDisplay, StringToDisplay, 10);
Send_stringwithLocation(x, y, StringToDisplay); send_string(" ");
}


void InitializeLCD(void)
{
	ddr_lcd_control|= 1 << RW| 1 << EN|1 << RS;
	_delay_ms(15);
	send_command(0x01); //clear the lcd
	_delay_ms(2);
	send_command(0x38); // 00DN F000; D- data length ,N- number of display lines,F- font size
	_delay_us(50);
	send_command(0b00001110);	//set the display on,cursor on, no blinking
	_delay_us(50);
}


#endif