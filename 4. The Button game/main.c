#include <avr/io.h>
#include <util/delay.h>

void ProcessPressedButton(int ButtonPressed);
void ProcessReleasedbutton(int ButtonReleased);

int pressed_confidence_level[2];
int released_confidence_level[2];
int pressed[2];
int LEDnumber[2];

int main(void)
{	
	//initialization area. Setting up ports and data direction registers
	DDRB = 0b01111111;
	DDRD = 0b01111111;
	PORTB = 0b10000000;
	PORTD = 0b10000000;
	while(1)
	{
		if (bit_is_clear (PINB,7))
		{
		  ProcessPressedButton(0);  //process clicks for side 1
		}
		else
		{
		  ProcessReleasedbutton(0);
		}
		if (bit_is_clear(PINB,7))
		{
		  ProcessPressedButton(1);	//process clicks for side 2
		}
		else
		{
		  ProcessReleasedbutton(1);
		}
		
	
	
	}



}

void ProcessPressedButton(int ButtonPressed)
{
	pressed_confidence_level[ButtonPressed] ++;
		  if (pressed_confidence_level[ButtonPressed]>600)
		  {
				if (pressed[ButtonPressed]==0)
				{
					pressed[ButtonPressed]=1;
					LEDnumber[ButtonPressed]++;
					if (ButtonPressed==0) PORTB |=1 << LEDnumber[ButtonPressed];
					if (ButtonPressed==1) PORTD |=1 << LEDnumber[ButtonPressed];
					if (LEDnumber[ButtonPressed]>6)
					{
						for (int i=0;i<10;i++)
						{
							if (ButtonPressed==0) PORTB= 0b10000000;
							if (ButtonPressed==1) PORTD= 0b10000000;
							_delay_ms(10);
							if (ButtonPressed==0) PORTB= 0b11111111;
							if (ButtonPressed==1) PORTD= 0b11111111;
							_delay_ms(10);
							
						}
						LEDnumber[0]=0;
						LEDnumber[1]=0;
					}
				}
			pressed_confidence_level[0]=0;
		  }


}

void ProcessReleasedbutton(int ButtonReleased)
{
	released_confidence_level[ButtonReleased]++;
			if (released_confidence_level[ButtonReleased]>600)
			{
				pressed[ButtonReleased]=0;
				released_confidence_level[ButtonReleased]=0;
			}
}