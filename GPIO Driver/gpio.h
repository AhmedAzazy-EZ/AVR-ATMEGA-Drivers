/*
 * gpio.h
 *
 * Created: 15-Jul-21 
 *  Author: Ahmed Azazy
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
typedef struct GPIO
{
	uint8_t PIN;
	uint8_t DDR;
	uint8_t PORT;	
}GPIO_t;


#define PORTA_BASE	(0x39)
#define GPIOA	((GPIO_t *) PORTA_BASE)

#define PORTB_BASE (0x36)
#define GPIOB	((GPIO_t *) PORTB_BASE)

#define PORTC_BASE (0x33)
#define GPIOC	((GPIO_t *) PORTC_BASE)

#define PORTD_BASE (0x30)
#define GPIOD	((GPIO_t *) PORTD_BASE)


/******************************************
			Function Prototypes
******************************************/
void clearBit(GPIO_t * GPIO , uint8_t bitNum);

void setBit(GPIO_t * GPIO , uint8_t bitNum);

/*******************************************/

#endif /* GPIO_H_ */
