/*
 * ADC.c
 *
 * Created: 10-Oct-21 
 *  Author: Ahmed Azazy
 */ 


#include <avr/io.h>
#include <stdint.h>
#include "ADC.h"

void ADC_Init(ADC_t * ADC_Ptr)
{
	ADMUX = 0;
	ADMUX |=(ADC_Ptr->ADC_ref << REFS0);
	ADMUX |= (ADC_Ptr->ADC_Adjust << ADLAR );
	ADMUX |= (ADC_Ptr->ADC_Input << MUX0);
	
	ADCSRA = 0 ; 
	ADCSRA|=(ADC_Ptr->ADC_mode <<  ADFR );
	ADCSRA|=(ADC_Ptr->ADC_Interrupt << ADIE);
	ADCSRA|=(ADC_Ptr->ADC_Prescaler << ADPS0);
	
	ADCSRA|= (ADC_Ptr->ADC_Enable << ADEN);
}


uint16_t ADC_Read(void)
{
	ADCSRA |= (1<<ADSC);
	volatile uint16_t * ADCL_Add = (uint16_t * )(0x24);
	while(!(ADCSRA & (1<<ADIF)));
	//Clear ADIF
	ADCSRA |=(1<<ADIF);
	return *ADCL_Add;
}