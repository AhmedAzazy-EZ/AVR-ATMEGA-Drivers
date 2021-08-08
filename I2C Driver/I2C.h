/*
 * I2C.h
 *
 * Created: 07-Aug-21 
 *  Author: Ahmed Azazy
 */ 


#ifndef I2C_H_
#define I2C_H_
#include <avr/io.h>


#define I2C_READ 1
#define I2C_WRITE 0

/**************Configurations**************/

#define I2C_BUFFER_LENGHT 100
#define MASTER_TRANS 0
#define MASTER_RECEIVE 1
#define SLAVE_TRANS 0
#define SLAVE_RECEIVE 0


/******************************************/

extern char I2C_Buffer[I2C_BUFFER_LENGHT];
extern uint16_t counter;
extern uint16_t I2C_DataLength;
extern uint8_t I2C_Mode ;


#if MASTER_TRANS == 1 || MASTER_RECEIVE == 1
	extern uint8_t target_Address;
#endif


typedef enum genteric
{
	DISABLE , 
	ENABLE	
}generic_t;

typedef enum I2C_Prescaler
{
	I2C_1_PRESCALER ,
	I2C_4_PRESCALER ,
	I2C_16_PRESCALER ,
	I2C_64_PRESCALER 
}I2C_Prescaler_t;

typedef struct I2c
{
	uint8_t I2c_BitRate;
	generic_t ACK_Generation;
	generic_t I2C_Enable;
	generic_t I2C_Interrupt;
	I2C_Prescaler_t I2C_prescaler;
	uint8_t I2C_address;
	generic_t I2C_GeneralCall;
}I2C_t;



void I2C_Init(I2C_t * i2c);
void I2C_SendStart(void );
void I2C_send(uint8_t );
void I2C_SendBuffer(void );
void I2C_SendAddress(void );
void I2C_SendStop(void );
#endif /* I2C_H_ */