/*
 * MI2C_Program.c
 *
 *  Created on: Jun 24, 2019
 *      Author: Hamza
 */


#include "LSTD_TYPES.h".
#include "LUTILS.h"


#include "MI2C_Interface.h"
#include "MI2C_private.h"



void MI2C_voidInit(void)
{

	SET_BIT(MI2C_TWCR,TWEN);//enable I2C module

	MI2C_TWBR=8;		//set TWBR=8 and set TWPS 0 and 0

	SET_BIT(MI2C_TWSR,TWPS0);	// to make the clock is 100 khz
	CLR_BIT(MI2C_TWSR,TWPS1);

	MI2C_TWAR=0x02;		// set my slave address as 0x01 and no general call

}

void MI2C_voidStartCondition(void)
{

	SET_BIT(MI2C_TWCR,TWSTA);//send start condtion

	MI2C_TWCR =(1<<TWINT) | (1<<TWSTA) | ( 1 << TWEN);
	while ((GET_BIT(MI2C_TWCR,TWINT)) == 0);//wait until start is transmitted

	MI2C_TWCR=(1<<TWEN);// clearing the start bit after sending

}

void MI2C_voidStopCondtion(void)
{
	MI2C_TWCR =(1<<TWINT) | (1<<TWSTO) | ( 1 << TWEN);

//	while ((GET_BIT(MI2C_TWCR,TWINT)) == 0);

}

u8 MI2C_u8CheckStatus(u8 ExpectedStatus)
{
	if ((MI2C_TWSR & 0xF8) == ExpectedStatus)
		return 1;
	else
			return 0;
}

void MI2C_voidSendSlaveAddress(u8 SLA,u8 Operation)
{
	MI2C_TWDR = (SLA<<1) | Operation;
	MI2C_TWCR= (1<<TWINT)  |  (1<<TWEN);
	while ((GET_BIT(MI2C_TWCR,TWINT)) == 0);
}

void MI2C_voidSendData(u8 Data)
{
	MI2C_TWDR = Data;
	MI2C_TWCR= (1<<TWINT)  |  (1<<TWEN);
	while ((GET_BIT(MI2C_TWCR,TWINT)) == 0);

}

u8 MI2C_u8ReceiveDataWithNoAck()
{
	MI2C_TWCR= (1<<TWINT)  |  (1<<TWEN);

	while ((GET_BIT(MI2C_TWCR,TWINT)) == 0);

	return MI2C_TWDR;

}

