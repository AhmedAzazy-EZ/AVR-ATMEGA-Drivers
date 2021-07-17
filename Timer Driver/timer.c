/*
 * timer.c
 *
 * Created: 17-Jul-21 2:02:02 AM
 *  Author: PC
 */ 

#include <stdlib.h>
#include "timer.h"

void TimerInit(_8BitTimer_t *tim)
	{
		if((void *)tim->instance == NULL)
			return ;
		
		volatile uint8_t * TCNT = NULL ;
		volatile uint8_t * TCCR = NULL;
		volatile uint8_t * OCR = NULL ;
		
		if(tim->instance == TIM0_BASE)
			{
				TCNT = (uint8_t *) (0x52);
				TCCR = (uint8_t *) (0x53);
				OCR = (uint8_t *) (0x5c);
				TIMSK |=(tim->OC_Interrupt << OCIE0);
				TIMSK |=(tim->OV_Interrupt << TOIE0);
			}
			
		else if(tim->instance == TIM2_BASE)
			{
				OCR = (uint8_t *) (0x43);
				TCNT = (uint8_t *) (0x44);
				TCCR = (uint8_t *) (0x45);
				if(tim->prescaler == _64_PRESCALER)
					{
						tim->prescaler = 4;
					}
					
				else if(tim->prescaler == _256_PRESCALER)
					{
						tim->prescaler = 6;
					}
					
				else if (tim->prescaler == _1024_PRESCALER)
					{
						tim->prescaler = 7;
					}
				TIMSK |=(tim->OC_Interrupt << OCIE2);
				TIMSK |=(tim->OV_Interrupt << TOIE2); 
			}
			
		*TCCR |= (tim->FOC << FOC_IDX);
		*TCCR |= WGM_VALUE(tim->WGM);
		*TCCR |= (tim->COM << COM_IDX);
		//*TCCR |= (tim.prescaler << CS_IDX);
		*TCNT = tim->TCNT;
		*OCR = tim->OCR;	
	}
	
	
void _8BitTimerStart(_8BitTimer_t *tim)
	{
		if((void *)tim->instance == NULL)
			return ;
			
		volatile uint8_t * TCCR = NULL;
		
		if(tim->instance == TIM0_BASE)
				TCCR = (uint8_t *) (0x53);
		else if(tim->instance == TIM2_BASE)
				TCCR = (uint8_t *) (0x45);
				
				
		*TCCR |= (tim->prescaler << CS_IDX);
	}
	
void _8BitTimerStop(_8BitTimer_t  *tim)
{
		if((void *)tim->instance == NULL)
		return ;
		
		volatile uint8_t * TCCR = NULL;
		
		if(tim->instance == TIM0_BASE)
		TCCR = (uint8_t *) (0x53);
		else if(tim->instance == TIM2_BASE)
		TCCR = (uint8_t *) (0x45);
		
		*TCCR &=~(7<<CS_IDX);	
}

uint8_t timerGetStatus(void)
	{
		return TIFR;	
	}