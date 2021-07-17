/*
 * timer.h
 *
 * Created: 17-Jul-21
 *  Author: Ahmed Azazy
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

#define TIM0_BASE	(uint8_t *) (0x52)	
#define TIM2_BASE	(uint8_t *) (0x43)


#define FOC_IDX		(7)
#define WGM_VALUE(x)	(((x&1)<<6)|((x&2)<<3))
#define COM_IDX	(4)
#define CS_IDX	(0)

typedef uint16_t timerBase_t;

typedef enum WGM_Mode
{
		NORMAL = 0 , 
		PHASE_CORRECT , 
		CTC , 
		PWM	
}WGM_t;

typedef enum CompareMode
{
	DISONNECTED = 0,
	TOGGLE_OC = 1 ,
	CLEAR_OC = 2,
	NON_INVERTING = 2,
	SET_OC = 3 , 
	INVERTING = 3	
}COM_t;

typedef enum TIM_Prescaler
{
	NO_CLOCK = 0 , 
	_1_PRESCALER = 1 , 
	_8_PRESCALER = 2,
	_32_PRESCALER = 3 ,
	_64_PRESCALER = 3, 
	_256_PRESCALER = 4 ,
	_128_PRESCALER = 5 ,
	_1024_PRESCALER = 5,
	EXTERNAL_FALLING_EDGE ,
	EXTERNAL_RAISING_EDGE	
}prescaler_t;

typedef enum generic
{
	DISABLE , 
	ENABLE	
}generic_t;	


typedef struct _8BitTimer
{
	uint8_t * instance;
	generic_t FOC;
	WGM_t WGM;
	COM_t COM;
	prescaler_t prescaler;
	uint8_t TCNT;
	uint8_t OCR;
	generic_t OC_Interrupt;
	generic_t OV_Interrupt;	
}_8BitTimer_t;


void TimerInit(_8BitTimer_t *);
void _8BitTimerStart(_8BitTimer_t *tim);
void _8BitTimerStop(_8BitTimer_t * tim);

uint8_t timerGetStatus(void );
#endif /* TIMER_H_ */
