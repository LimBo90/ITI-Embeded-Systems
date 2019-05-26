#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

/******* PINS *******/
#define MDIO_PIN_0		0
#define MDIO_PIN_1		1
#define MDIO_PIN_2		2
#define MDIO_PIN_3		3
#define MDIO_PIN_4		4
#define MDIO_PIN_5		5
#define MDIO_PIN_6		6
#define MDIO_PIN_7		7
#define MDIO_PIN_8		8
#define MDIO_PIN_9		9
#define MDIO_PIN_10	    10
#define MDIO_PIN_11	    11
#define MDIO_PIN_12	    12
#define MDIO_PIN_13	    13
#define MDIO_PIN_14	    14
#define MDIO_PIN_15	    15

/****** PORTS *****/
#define MDIO_PORTA 	0
#define MDIO_PORTB 	1
#define MDIO_PORTC 	2
#define MDIO_PORTD 	3
#define MDIO_PORTE 	4
#define MDIO_PORTF 	5
#define MDIO_PORTG 	6

#define DIO_U8_HIGH 1
#define DIO_U8_LOW 0

/*********Digital pin directions/*********/
//General purpose output
#define MDIO_MODE_OUTPUT_PUSHPULL_10      0b0001
#define MDIO_MODE_OUTPUT_PUSHPULL_2       0b0010
#define MDIO_MODE_OUTPUT_PUSHPULL_50      0b0011
#define MDIO_MODE_OUTPUT_OPENDRAIN_10     0b0101
#define MDIO_MODE_OUTPUT_OPENDRAIN_2      0b0110
#define MDIO_MODE_OUTPUT_OPENDRAIN_50     0b0111
//Alternate function output
#define MDIO_MODE_AF_OUTPUT_PUSHPULL_10      0b1001
#define MDIO_MODE_AF_OUTPUT_PUSHPULL_2       0b1010
#define MDIO_MODE_AF_OUTPUT_PUSHPULL_50      0b1011
#define MDIO_MODE_AF_OUTPUT_OPENDRAIN_10     0b1101
#define MDIO_MODE_AF_OUTPUT_OPENDRAIN_2      0b1110
#define MDIO_MODE_AF_OUTPUT_OPENDRAIN_50     0b1111
//Input
#define MDIO_MODE_INPUT_ANALOG               0b0000
#define MDIO_MODE_INPUT_FLOATING             0b0100
#define MDIO_MODE_INPUT_PULLUP               0b1000
#define MDIO_MODE_INPUT_PULLDOWN             0b1100

void MDIO_voidInit(void);
void MDIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8PinVal);
void MDIO_voidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_u8PinVal);
void MDIO_voidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_PinMode);
void MDIO_voidSetPortMode(u8 Copy_u8Port, u16 Copy_u8Mask, u8 Copy_PinMode);
void MDIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u8Mask, u16 Copy_u8Value);
#endif
