/*
 * Timer Derivers.c
 *
 * Created: 17-Jul-21 1:01:32 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include "timer.h"

_8BitTimer_t tim0;
_8BitTimer_t tim2;
int main(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;
    tim0.instance = TIM0_BASE;
	tim0.FOC = DISABLE;
	tim0.WGM = PWM;
	tim0.COM = NON_INVERTING ;
	tim0.prescaler = _1024_PRESCALER;
	tim0.TCNT = 0;
	tim0.OCR = 156;
	tim0.OC_Interrupt = DISABLE;
	tim0.OV_Interrupt = DISABLE;
	
	
	    tim2.instance = TIM2_BASE;
	    tim2.FOC = DISABLE;
	    tim2.WGM = PWM;
	    tim2.COM = NON_INVERTING ;
	    tim2.prescaler = _1024_PRESCALER;
	    tim2.TCNT = 0;
	    tim2.OCR = 156;
	    tim2.OC_Interrupt = DISABLE;
	    tim2.OV_Interrupt = DISABLE;
	TimerInit(&tim2);
	TimerInit(&tim0);
	
	_8BitTimerStart(&tim0);
	_8BitTimerStart(&tim2);
	asm("nop");
    while (1) 
    {
    }
}

