#include "LUTILS.h"
#include "LSTD_TYPES.h"

#include <MRCC_interface.h>
#include <MRCC_private.h>

void MRCC_voidInit(void){
	MRCC -> CR = 0x00010000;
	MRCC -> CFGR = 0x00000001;
}

void MRCC_voidEnPeriphClk(u8 Copy_u8PeriphIdx)
{
	u8 Local_u8Bus = Copy_u8PeriphIdx / MRCC_U8_REG_SIZE;
	u8 Local_u8Peripheral = Copy_u8PeriphIdx %  MRCC_U8_REG_SIZE;

	switch(Local_u8Bus)
	{
		case MRCC_U8_AHB:	LUTILS_SET_BIT(MRCC->AHBENR, Local_u8Peripheral);	break;
		case MRCC_U8_APB1:	LUTILS_SET_BIT(MRCC->APB1ENR, Local_u8Peripheral);	break;
		case MRCC_U8_APB2:	LUTILS_SET_BIT(MRCC->APB2ENR, Local_u8Peripheral);	break;
		default:	/*Report Error */											break;
	}
}

void MRCC_voidDsPeriphClk(u8 Copy_u8PeriphIdx)
{
	u8 Local_u8Bus = Copy_u8PeriphIdx / MRCC_U8_REG_SIZE;
	u8 Local_u8Peripheral = Copy_u8PeriphIdx %  MRCC_U8_REG_SIZE;

	switch(Local_u8Bus)
	{
		case MRCC_U8_AHB:	LUTILS_CLR_BIT(MRCC->AHBENR, Local_u8Peripheral);	break;
		case MRCC_U8_APB1:	LUTILS_CLR_BIT(MRCC->APB1ENR, Local_u8Peripheral);	break;
		case MRCC_U8_APB2:	LUTILS_CLR_BIT(MRCC->APB2ENR, Local_u8Peripheral);	break;
		default:	/*Report Error */											break;
	}
}
