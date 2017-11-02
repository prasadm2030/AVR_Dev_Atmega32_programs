#include <avr/io.h>
#include<util/delay.h>

int main(void)
{	
	DDRD=0XFF;
	TCCR1A |= 1 << WGM11| 1 << COM1A1 | 1 << COM1A0;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
	ICR1= 22000;
	
	void speed(int delay);
	while(1)
	{	
		speed(20000);
	}
}



void speed(int factor)
	{
	OCR1A= ICR1-factor;
	}

