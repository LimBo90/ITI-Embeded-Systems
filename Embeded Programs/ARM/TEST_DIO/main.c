
#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MRCC_interface.h"

void main(){
	u32 i;
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOC);
	MDIO_voidInitialize();
	while(1){
		for(i = 0; i < 4000000; i++){
			asm("NOP");
		}
		MDIO_voidSetPinValue(DIO_U8_PIN32, DIO_U8_LOW);

		for(i = 0; i < 4000000; i++){
					asm("NOP");
		}
		MDIO_voidSetPinValue(DIO_U8_PIN32, DIO_U8_HIGH);
	}
}
