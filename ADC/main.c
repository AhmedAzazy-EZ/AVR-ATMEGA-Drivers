#include <avr/io.h>
#include <stdlib.h>
#include "ADC.h"
uint16_t readValue = 0;
int main(void)
{
	
	DDRF = 0x00;
	ADC_t * ADC_Ptr = (ADC_t *) calloc(1 , sizeof(ADC_t ));
	ADC_Ptr->ADC_Adjust = LEFT;
	ADC_Ptr->ADC_Enable = ENABLE ; 
	ADC_Ptr->ADC_Input = ADC0 , 
	ADC_Ptr->ADC_mode = SINGLE_CONVERSION ; 
	ADC_Ptr->ADC_Interrupt = DISABLE ; 
	ADC_Ptr->ADC_Prescaler = ADC_128_PRESCALE ;
	ADC_Ptr->ADC_ref = AVCC;
	
	
	ADC_Init(ADC_Ptr);
	free(ADC_Ptr);
	
	
	uint16_t  i ;
    while (1) 
    {
		readValue = ADC_Read();
		for(i=0 ; i < 60000 ;  i++);
    }
}

