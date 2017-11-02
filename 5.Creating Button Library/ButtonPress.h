#ifndef ButtonPress
#define ButtonPress

#include <avr/io.h>

char ButtonPressed(int ButtonNumber,unsigned char pinOfButton, unsigned char portBit,int confidence_level);

	char pressed[numberofButtons];
	int pressed_confidence_level[numberofButtons];
	int released_confidence_level[numberofButtons];

	
char ButtonPressed(int ButtonNumber,unsigned char pinOfButton, unsigned char portBit,int confidence_level)
{
	
	if (bit_is_set(pinOfButton,portBit))
	{
		pressed_confidence_level[ButtonNumber]++;
		released_confidence_level[ButtonNumber]=0;
		if (pressed_confidence_level[ButtonNumber] > confidence_level)
		{
			if(pressed[ButtonNumber] == 0)
			{
				pressed[ButtonNumber] = 1;
				pressed_confidence_level[ButtonNumber]=0;
				return 1;
			}
		}
	}
	
	else
	{
		released_confidence_level[ButtonNumber]++;
		pressed_confidence_level[ButtonNumber]=0;
		if (released_confidence_level[ButtonNumber] > confidence_level)
		{
		pressed[ButtonNumber] = 0;
		released_confidence_level[ButtonNumber]=0;
		}
	}
	return 0;
}
#endif
