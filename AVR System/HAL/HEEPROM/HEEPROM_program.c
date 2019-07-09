/*
 * HEEPROM_program.c
 *
 *  Created on: Jun 27, 2019
 *      Author: Abdelrahman
 */

#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MI2C_Interface.h"
#include "HEEPROM_interface.h"

void HEEPROM_voidInit(void){
	MI2C_voidInit();
}


void HEEPROM_voidWriteByte(u16 Copy_u16Location, u8 Copy_u8Byte){
	Copy_u16Location &= 0x03FF;
	u8 loc = (u8)Copy_u16Location;
	u8 SLA = HEEPROM_ADDRESS | Copy_u16Location >> 8;


	MI2C_voidStartCondition();
	if(MI2C_u8CheckStatus(0x08) == 0)
		return;


	MI2C_voidSendSlaveAddress(SLA, MI2C_OPERATION_WRITE);
	if(MI2C_u8CheckStatus(0x18) == 0)
		return;

	MI2C_voidSendData(loc);
	if(MI2C_u8CheckStatus(0x28) == 0)
		return;

	MI2C_voidSendData(Copy_u8Byte);
	if(MI2C_u8CheckStatus(0x28) == 0)
		return;

	MI2C_voidStopCondtion();
}

void HEEPROM_voidReadByte(u16 Copy_u16Location, u8 * data){
	Copy_u16Location &= 0x03FF;
	u8 loc = (u8)Copy_u16Location;
	u8 SLA = HEEPROM_ADDRESS | Copy_u16Location >> 8;

	//Start condition
	MI2C_voidStartCondition();
	if(MI2C_u8CheckStatus(0x08) == 0)
		return;

	//SLA+W
	MI2C_voidSendSlaveAddress(SLA, MI2C_OPERATION_WRITE);
	if(MI2C_u8CheckStatus(0x18) == 0)
		return;


	//send location
	MI2C_voidSendData(loc);
	if(MI2C_u8CheckStatus(0x28) == 0)
		return;

	//send repeated start
	MI2C_voidStartCondition();
	if(MI2C_u8CheckStatus(0x10) == 0)	//repeated start
		return;

	//SLA+R
	MI2C_voidSendSlaveAddress(SLA, MI2C_OPERATION_READ);
	if(MI2C_u8CheckStatus(0x40) == 0)
		return;

	//read data from slave
	*data = MI2C_u8ReceiveDataWithNoAck();

	MI2C_voidStopCondtion();

//	HLCD_writeData('M');
}
