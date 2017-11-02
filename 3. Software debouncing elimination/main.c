#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB|=1 <<PINB0;	//DATA DIECTION REGISTER OUTPUT PIN0
	PORTB^=1 <<PINB0;	//TOGGLE PINB0 
	DDRB|= 1 <<PINB2;	//DATA DIRECTION REGISTER OUTPUT PIN2
	DDRB&= ~(1 <<PINB1);	//DATA DIRECTION REGISTER INPUT PIN1
	PORTB|= 1 <<PINB1;	//SET PIN1 HIGH
	int pressed=0;
	int pressed_confidence_level=0;
	int released_confidence_level=0;
	
	while(1)
	{
	
	if (bit_is_clear(PINB,1))
	{
		pressed_confidence_level++;
		if (pressed_confidence_level>600)
		{
			if(pressed == 0)
			{
				PORTB^= 1 <<PINB0;
				PORTB^= 1 <<PINB2;
				pressed = 1;
				pressed_confidence_level=0;
			}
		}
	}
	
	else
	{
		released_confidence_level++;
		if (released_confidence_level>600)
		{
		pressed = 0;
		released_confidence_level=0;
		}
	}
  }

}