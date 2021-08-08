/*
 * I2C.c
 *
 * Created: 07-Aug-21 
 *  Author: Ahmed Azazy
 */ 

/***********************************************************************
						 | NOTES |
						  ------

1) In case of Slave Receiver mode , you have to Enable Ack generation 
	before anytime you use it.
	
	
*************************************************************************/

#include "I2C.h"
#include <avr/interrupt.h>

char I2C_Buffer[I2C_BUFFER_LENGHT];
uint16_t counter = 0;
uint16_t I2C_DataLength = 0;
uint8_t I2C_Mode ;
uint8_t try_again = 0;

#if MASTER_TRANS==1 || MASTER_RECEIVE == 1
	uint8_t target_Address = 0;
#endif



void I2C_Init(I2C_t * i2c)
{
	TWBR = i2c->I2c_BitRate;
	TWCR |=(i2c->ACK_Generation << TWEA);
	TWCR |= (i2c->I2C_Enable << TWIE);
	TWSR |= (i2c->I2C_prescaler);
	TWAR = i2c->I2C_address;
	TWAR |=(i2c->I2C_GeneralCall);
	TWCR |=(i2c->I2C_Enable << TWEN);
}




void I2C_send(uint8_t data)
{
	TWDR = data;
	//clear TWINT to start transmission
	TWCR |= (1<<TWINT);
}

void I2C_SendBuffer()
{
	
	while(I2C_Buffer[counter])
		{
			I2C_send(I2C_Buffer[counter]);
			counter++;
		}
		
	counter = 0;
}



#if MASTER_TRANS==1 || MASTER_RECEIVE == 1

void I2C_SendStart(void )
{
	TWCR |= (1<<TWINT) | (1<<TWSTA);
}

void I2C_SendStop(void )
{
	TWCR |= (1<<TWINT) | (1<<TWSTO);
}


void I2C_SendAddress(void )
{
	I2C_send(target_Address | I2C_Mode);
	try_again++;
}
#endif

ISR(TWI_vect)
{	
	switch(TWSR & 0xF8)
	{
		#if MASTER_TRANS == 1
		//A START condition has been transmitted
		case 0x08 :
			//TWCR |= (1<<TWINT);
			I2C_SendAddress();
			break ;
			
		//SLA+W has been transmitted; ACK has been received
		case 0x18 : 
			I2C_send(I2C_Buffer[0]);
			counter = 1;
			try_again = 0;
			break;
			
		//SLA+W has been transmitted; NOT ACK has been received
		case 0x20 :
			I2C_SendAddress();
			if(try_again == 10)
			{
				I2C_SendStop();
				try_again = 0;
			}
			break;
		
		//Data byte has been transmitted; ACK has been received	
		case 0x28 :
			I2C_send(I2C_Buffer[counter]);
			counter++;
			if(counter == I2C_DataLength)
				{
					I2C_SendStop();
					counter = 0;
				}
			break;
		
		
		//Data byte has been transmitted; NOT ACK has been received
		case 0x30 : 
			counter--;
			I2C_send(I2C_Buffer[counter]);
			counter++;
			try_again++;
			if(try_again == 10)
			{
				I2C_SendStop();
				try_again = 0;
			}
			break;
		
		//Arbitation Lost
		case 0x38 : 
			counter = 0 ;
			try_again = 0 ;
			TWCR |= (1<<TWINT);	
			break ;
			
//-------------------------Master Receive----------

		#elif MASTER_RECEIVE == 1
		
		//A START condition has been transmitted
		case 0x08 :
		I2C_SendAddress();
		break ;
		
		//Arbitration Lost
		case 0x38 :
			counter = 0 ;
			try_again = 0 ;
			TWCR |= (1<<TWINT); 
			break ;
		//SLA+R has been transmitted; ACK has been received	
		case 0x40 : 
			try_again = 0;
			TWCR |= (1<<TWINT);
			break;
			
		//SLA+R has been transmitted; NOT ACK has been received		
		case 0x48 : 
			I2C_SendAddress();
			try_again++;
			if(try_again == 10)
			{
				I2C_SendStop();
				try_again = 0;
			}
			break;
			

		//Data byte has been received; ACK has been returned				
		case 0x50 : 
			I2C_Buffer[counter] = TWDR ;
			counter++;
			TWCR |=(1<<TWINT);
			if(counter == I2C_DataLength)
				{
					I2C_SendStop();
					counter = 0;
					try_again = 0;
				}
			break ;
			
		//Data byte has been received; NOT ACK has been returned
		case 0x58 : 
			I2C_SendStop();
			break;

//-----------------------------Slave TRANS------------------
		#elif SLAVE_TRANS == 1
		
		//Own SLA+R has been received; ACK has been returned
		case 0xA8 :
		case 0xB0 :
			 I2C_send(I2C_Buffer[counter++]);
			break;
		
		//Data byte in TWDR has been transmitted; ACK has been received
		case 0xB8 : 
		I2C_send(I2C_Buffer[counter++]);
		if(counter == I2C_DataLength)
		{
			//virtually disconnect the device.
			counter = 0;
			try_again = 0;
			TWCR &=~(1<<TWEA);
			TWCR |=(1<<TWINT);
		} 
		break;
		
		
		// Data byte in TWDR has been transmitted; NOT ACK has been received
		case 0xC0 : 
			counter--;
			I2C_send(I2C_Buffer[counter++]);
			try_again++;
			if(try_again == 10)
			{
			counter = 0;
			try_again = 0;
			TWCR &=~(1<<TWEA);
			TWCR |=(1<<TWINT);	
			}
			break;
			
		case 0xC8 : 
			TWCR &=~(1<<TWEA);
			TWCR |= (1<<TWINT);
			break;


//-------------------------SLAVE RECEIVER-------------------
			
		#elif SLAVE_RECEIVE == 1
		
		// Own SLA+W has been received; ACK has been returned
		case 0x60 :
		case 0x70 :
		case 0x78 :
		case 0x68 : 
			TWCR |=(1<<TWINT);
			break ;
		
		// Previously addressed with own SLA+W; data has been received; ACK has been returned
		case 0x80 :
		case 0x90 : 
		I2C_Buffer[counter++] = TWDR;
		if(counter == I2C_DataLength)
		{
			try_again = 0;
			counter = 0;
			TWCR &=~(1<<TWEA);
		}
		TWCR |= (1<<TWINT);
		break;
		
		case 0xA0 : 
		TWCR |=(1<<TWINT);
		break;
		
		#endif

	}
	
}
