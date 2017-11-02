#include <avr/io.h>
#include <util/delay.h>

void blinkport(unsigned char portBit);
int main (void)
{
	DDRB = 0b11111111;
	DDRD = 0b00000111;	
	while(1)
	{	
		
		_delay_ms(100);
		PORTB = 0b00000001;
		_delay_ms(10);
		PORTD|= 1<< PIND0;
		_delay_ms(10);
		PORTD|= 1<< PIND1;
		_delay_ms(10);
		PORTD|= 1<< PIND2;
		_delay_ms(10);
		PORTD|= 1<< PIND3;
		_delay_ms(10);
		PORTD = 0b00001000;
		PORTB = 0b00100001;
		_delay_ms(10);
		PORTB = 0b00111001;
		_delay_ms(10);
		
		PORTB = 0b00000000;
		PORTD = 0b00000000;
	}
	
}

void blinkport(unsigned char portBit)
{
		PORTB ^= 1 << portBit;
		_delay_ms(5);
		PORTB ^= 1 << portBit;
		_delay_ms(0.2);
}

