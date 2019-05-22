#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MRCC_interface.h"


#define C1	MDIO_PIN_14
#define R1	MDIO_PIN_12
#define LED	MDIO_PIN_13
void main(){
	u32 i;
	u8 value;
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOC);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOA);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOB);
	MDIO_voidSetPinMode(MDIO_PORTB, C1, MDIO_MODE_OUTPUT_PUSHPULL_2);
	MDIO_voidSetPinMode(MDIO_PORTB, LED, MDIO_MODE_OUTPUT_PUSHPULL_2);
	MDIO_voidSetPinMode(MDIO_PORTB, R1, MDIO_MODE_INPUT_PULLDOWN);

	MDIO_voidSetPinValue(MDIO_PORTB, C1, DIO_U8_HIGH);
//	MDIO_voidInit();
	while(1){
		MDIO_voidGetPinValue(MDIO_PORTB, R1, &value);
		MDIO_voidSetPinValue(MDIO_PORTB, LED, value);
//		for(i = 0; i < 250000; i++){
//			asm("NOP");
//		}
//		MDIO_voidSetPinValue(MDIO_PORTB, MDIO_PIN_12, DIO_U8_LOW);
//		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_15, DIO_U8_LOW);
//
//		for(i = 0; i < 250000; i++){
//			asm("NOP");
//		}
//		MDIO_voidSetPinValue(MDIO_PORTB, MDIO_PIN_12, DIO_U8_HIGH);
//		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_15, DIO_U8_HIGH);
	}
}
