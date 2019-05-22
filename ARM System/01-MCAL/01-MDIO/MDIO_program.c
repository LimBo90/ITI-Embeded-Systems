#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MDIO_private.h"

void MDIO_voidInit(void){
//	MDIO_GPIOC->CR = 0x2222222200000000;
//	MDIO_GPIOA->CR = 0x0002000000000000;
//	MDIO_GPIOB->CR = 0x0000000000000000;

}

void MDIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8PinVal){
	if(Copy_u8PinVal == DIO_U8_HIGH)
	{
		switch(Copy_u8Port)
		{
			case MDIO_PORTA:	LUTILS_SET_BIT(MDIO_GPIOA->ODR, Copy_u8Pin);	break;
			case MDIO_PORTB:	LUTILS_SET_BIT(MDIO_GPIOB->ODR, Copy_u8Pin);	break;
			case MDIO_PORTC:	LUTILS_SET_BIT(MDIO_GPIOC->ODR, Copy_u8Pin);	break;
			default: /* Report Error */ 										break;
		}
	}
	else if(Copy_u8PinVal == DIO_U8_LOW)
	{
		switch(Copy_u8Port)
		{
			case MDIO_PORTA:	LUTILS_CLR_BIT(MDIO_GPIOA->ODR, Copy_u8Pin);	break;
			case MDIO_PORTB:	LUTILS_CLR_BIT(MDIO_GPIOB->ODR, Copy_u8Pin);	break;
			case MDIO_PORTC:	LUTILS_CLR_BIT(MDIO_GPIOC->ODR, Copy_u8Pin);	break;
			default: /* Report Error */ 										break;
		}
	}
}

void MDIO_voidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_u8PinVal){
	switch(Copy_u8Port)
	{
		case MDIO_PORTA:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOA->IDR, Copy_u8Pin);	break;
		case MDIO_PORTB:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOB->IDR, Copy_u8Pin);	break;
		case MDIO_PORTC:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOC->IDR, Copy_u8Pin);	break;
		default: /* Report Error */ 														break;
	}
}

void MDIO_voidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_PinMode){
	u8 Local_u8PullUP = 2;	//not input

	if (Copy_PinMode == MDIO_MODE_INPUT_PULLUP || Copy_PinMode == MDIO_MODE_INPUT_PULLDOWN){
		Local_u8PullUP = Copy_PinMode & 1;
		Copy_PinMode >>= 1;
	}

	switch(Copy_u8Port)
	{
		case MDIO_PORTA:
			MDIO_GPIOA->CR &= (~((u64)0x0F << (Copy_u8Pin*4)));
			MDIO_GPIOA->CR |=  ((u64)Copy_PinMode << (Copy_u8Pin*4));
			if(Local_u8PullUP == 0)	//input pull up
				LUTILS_CLR_BIT(MDIO_GPIOA->ODR, Copy_u8Pin);
			else if(Local_u8PullUP == 1)	//input pull down
				LUTILS_SET_BIT(MDIO_GPIOA->ODR, Copy_u8Pin);
			break;
		case MDIO_PORTB:
			MDIO_GPIOB->CR &= (~((u64)0x0F << (Copy_u8Pin*4)));
			MDIO_GPIOB->CR |= ((u64)Copy_PinMode << (Copy_u8Pin*4));
			if(Local_u8PullUP == 0)	//input pull up
				LUTILS_CLR_BIT(MDIO_GPIOB->ODR, Copy_u8Pin);
			else if(Local_u8PullUP == 1)
				LUTILS_SET_BIT(MDIO_GPIOB->ODR, Copy_u8Pin);
			break;
		case MDIO_PORTC:
			MDIO_GPIOC->CR &= (~((u64)0x0F << (Copy_u8Pin*4)));
			MDIO_GPIOC->CR |= ((u64)Copy_PinMode << (Copy_u8Pin*4));
			if(Local_u8PullUP == 0)	//input pull up
				LUTILS_CLR_BIT(MDIO_GPIOC->ODR, Copy_u8Pin);
			else if(Local_u8PullUP == 1)	//input pull down
				LUTILS_SET_BIT(MDIO_GPIOC->ODR, Copy_u8Pin);
			break;
		default:
			/* Report Error */
			break;
	}
}

