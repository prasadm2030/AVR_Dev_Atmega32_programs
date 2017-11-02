#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 1 << PINB0 | 1 << PINB2;	//PINB0 is the switch state (On/Off) sensing pin, PINB1 drives a buzzer to define the switch action
	
	while (1)
	{
		if (bit_is_clear(PINB,1))	//Pull down switch configuration
		{
			PORTB|= 1 << PINB2;
		}
	
	//if (bit_is_set(PINB,1))	//Pull UP switch configuration (if needed)
		{
			PORTB|= 1 << PINB2;
		}
	}
}