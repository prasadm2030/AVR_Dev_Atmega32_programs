#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include "LCD.h"

int main (void)
{
	InitializeLCD();
	//configure the ADC 
	ADCSRA |= 1 << ADPS2;	//enable a prescaler- determined by internal/external clock  
	ADMUX |= 1 << ADLAR;	//8-BIT result
	ADMUX |= 1 << 1 << REFS0;	//SET AVcc as the reference voltage
	ADCSRA |=1 << ADIE;		//enable the interrupt function in ADC
	ADCSRA |= 1 << ADEN;	//turn on the ADC feature
	sei();//enable global interrupts
	
	ADCSRA |= 1 << ADSC;//start the first conversion
	
	while(1)
	{
	
	}
}


ISR (ADC_vect)//*******ADC INTERRUPT ROUTINE
{
	char adcResult[4];//LCD string variable declaration
	itoa(ADCH,adcResult,10);//converting the adc result into a string
	GotoLocation(1,1);
	send_string(adcResult);//displaying the string
	send_string(" ");//displaying the string

	ADCSRA |= 1 << ADSC;//doing the next conversion
}