#define numberofButtons 2
#include <avr/io.h>
#include "ButtonPress.h"

int main (void)
{
	DDRB = 0b00001100;
	PORTB = (0 << PINB0)|(0 << PINB1);
	
	while(1)
	{
		if (ButtonPressed(0,PINB, 0,600))
		{
			PORTB|= 1 << PINB2;
		}
		
		if (ButtonPressed(1,PINB, 1,600))
		{
			PORTB|= 1 << PINB3;
		}
	}
}



