/*
 * ADC.h
 *
 * Created: 10-Oct-21
 *  Author: Ahmed Azazy
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef enum generic
{
	DISABLE , 
	ENABLE	
}generic_t;

typedef enum refrence_selc
{
	AREF , 
	AVCC , 
	INTERNAL = 3
}RefrenceSelc_t;

typedef enum adjustment 
{
	LEFT , 
	RIGHT
}Adjustment_t;

typedef enum input_selec
{
	ADC0 , 
	ADC1 , 
	ADC2 , 
	ADC3 , 
	ADC4 , 
	ADC5 , 
	ADC6 , 
	ADC7 ,
	
	
	//Differential input with gain 
	ADC0_ADC0_x10 , 
	ADC1_ADC0_x10 , 
	ADC0_ADC0_x200 , 
	ADC1_ADC0_x200 , 
	ADC2_ADC2_x10 , 
	ADC3_ADC2_x10 , 
	ADC2_ADC2_x200 , 
	ADC3_ADC2_x200 ,
	ADC0_ADC1_x1 , 
	ADC1_ADC1_x1 , 
	ADC2_ADC1_x1 , 
	ADC3_ADC1_x1 , 
	ADC4_ADC1_x1 , 
	ADC5_ADC1_x1 , 
	ADC6_ADC1_x1 , 
	ADC7_ADC1_x1 , 
	ADC0_ADC2_x1 , 
	ADC1_ADC2_x1 ,
	ADC2_ADC2_x1 ,
	ADC3_ADC2_x1 ,
	ADC4_ADC2_x1 ,
	ADC5_ADC2_x1 ,
	IN_Vbg , 
	IN_GND
}input_selec_t;

typedef enum ADC_FreeRunning_selc
{
	SINGLE_CONVERSION , 
	FREE_RUNNING
}ADC_FreeRunning_Selc_t;

typedef enum ADC_prescaler
{
	ADC_2_PRESCALE , 
	ADC_4_PRESCALE = 2 , 
	ADC_8_PRESCALE , 
	ADC_16_PRESCALE , 
	ADC_32_PRESCALE ,
	ADC_64_PRESCALE ,
	ADC_128_PRESCALE 
}ADC_Prescaler_t;



typedef struct Type_ADC 
{
	RefrenceSelc_t ADC_ref ;
	Adjustment_t   ADC_Adjust ; 
	input_selec_t ADC_Input ;
	generic_t  ADC_Enable ; 
	ADC_FreeRunning_Selc_t	ADC_mode ; 
	generic_t	ADC_Interrupt ; 
	ADC_Prescaler_t	ADC_Prescaler;
}ADC_t;


void ADC_Init(ADC_t *);

uint16_t ADC_Read(void);

#endif /* ADC_H_ */