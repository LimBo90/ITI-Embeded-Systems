#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MRCC_interface.h"
#include "MTIMER2_interface.h"
#include "HLCD_interface.h"

void init(){
	MRCC_voidInit();
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOA);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOB);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOC);
	MDIO_voidInit();
	MDIO_voidSetPortMode(MDIO_PORTA, 0x01FF, MDIO_MODE_OUTPUT_PUSHPULL_2);

	MDIO_voidSetPinMode(MDIO_PORTB, MDIO_PIN_4, MDIO_MODE_INPUT_PULLDOWN);
//	MDIO_voidSetPinMode(MDIO_PORTB, MDIO_PIN_3, MDIO_MODE_INPUT_PULLDOWN);
//	MDIO_voidSetPinMode(MDIO_PORTB, MDIO_PIN_5, MDIO_MODE_INPUT_PULLDOWN);
//	MDIO_voidSetPinMode(MDIO_PORTB, MDIO_PIN_4, MDIO_MODE_INPUT_PULLDOWN);

}
void main(){
	init();
	u32 i;
	MDIO_voidSetPinValue(MDIO_PORTA, MDIO_PIN_8, DIO_U8_LOW);
	while(1){
		u8 R1 ,R2, R3, R4;
		MDIO_voidGetPinValue(MDIO_PORTB, MDIO_PIN_4, &R1);
//		MDIO_voidGetPinValue(MDIO_PORTB, MDIO_PIN_3, &R2);
//		MDIO_voidGetPinValue(MDIO_PORTB, MDIO_PIN_5, &R3);
//		MDIO_voidGetPinValue(MDIO_PORTB, MDIO_PIN_4, &R4);

		MDIO_voidSetPinValue(MDIO_PORTA, MDIO_PIN_0, R1);
		MDIO_voidSetPinValue(MDIO_PORTA, MDIO_PIN_1, R1);
		MDIO_voidSetPinValue(MDIO_PORTA, MDIO_PIN_2, R1);
		MDIO_voidSetPinValue(MDIO_PORTA, MDIO_PIN_3, R1);

//		MDIO_voidSetPortValue(MDIO_PORTA, 0x00FF, 0x00FF);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_13, DIO_U8_HIGH);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_14, DIO_U8_HIGH);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_15, DIO_U8_HIGH);
//		for(i = 250000; i > 0; i--)
//			asm("NOP");
//
//		MDIO_voidSetPortValue(MDIO_PORTA, 0x00FF, 0x0000);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_13, DIO_U8_LOW);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_14, DIO_U8_LOW);
////		MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_15, DIO_U8_LOW);
//		for(i = 250000; i > 0; i--)
//			asm("NOP");
	}
}
