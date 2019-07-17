/*
 * UART_Program.c

 *
 *  Created on: Jul 12, 2019
 *      Author: Hamza
 */


#include "LSTD_Types.h"
#include "LUTILS.h"

#include "UART_Interface.h"
#include "UART_Private.h"

void MUART_voidInit(void)
{
	LUTILS_SET_BIT(MUART_CR1,UE);

	LUTILS_CLR_BIT(MUART_CR1,M);

	LUTILS_CLR_BIT(MUART_CR1,PCE);

	LUTILS_SET_BIT(MUART_CR1,TE);

	LUTILS_SET_BIT(MUART_CR1,RE);

	LUTILS_CLR_BIT(MUART_CR2,STOP0);
	LUTILS_CLR_BIT(MUART_CR2,STOP1);

	MUART_BRR=0x8A;




}

void MUART_voidSendChar(u8 copy_data)
{
	MUART_DR=copy_data;

	while(LUTILS_GET_BIT(MUART_SR,TC)==0);
}

void MUART_voidSendString(u8* copy_data)
{
	u8 offset=0;
	do{
		MUART_voidSendChar(copy_data[offset]);
		offset++;
	}while(copy_data[offset-1] != '\r');
}

/**
 * Receives a character through UART, blocks CPU until character is received or timeout.
 * Returns MUART_COMPLETE or MUART_TIMEOUT
 */
u8 MUART_u8ReceiveChar(u32 Copy_u32Timeout, u8 * data)
{
	u8 status;
	while(Copy_u32Timeout && LUTILS_GET_BIT(MUART_SR,RXNE)==0){
		Copy_u32Timeout--;
	}
	if(Copy_u32Timeout == 0){
		status = MUART_TIMEOUT;
	}else{
		status = MUART_COMPLETE;
		*data = MUART_DR;
	}
	return status;
}

/**
 * Receives a string through UART, blocks CPU until string is received or timeout.
 * Returns MUART_COMPLETE or MUART_TIMEOUT
 */
u8 MUART_u8ReceiveString(u32 Copy_u32Timeout, u8 * str)
{
	u8 status = MUART_COMPLETE;
	u8 offset=0;
	u32 time;
	do
	{
		time = Copy_u32Timeout;
		while(time && LUTILS_GET_BIT(MUART_SR,RXNE)==0){
			time--;
		}

		if(time == 0){
			status = MUART_TIMEOUT;
			break;
		}

		u8 rvalue = MUART_DR;
		str[offset]=rvalue;
		offset++;
	}while(str[offset-1] != '\r');

	return status;

}

