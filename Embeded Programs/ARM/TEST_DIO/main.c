#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MRCC_interface.h"

#define PORT MDIO_PORTA


void main(){
	u32 i;
	u8 value;
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOC);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOA);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOB);
	MDIO_voidSetPortMode(PORT, 0x00FF, MDIO_MODE_OUTPUT_PUSHPULL_2);
	while(1){

		for(value = 1; value > 0; value<<=1){
			MDIO_voidSetPortValue(PORT, 0x00FF, value);
			for(i = 0; i < 250000; i++)
				asm("NOP");
		}

	}
}
