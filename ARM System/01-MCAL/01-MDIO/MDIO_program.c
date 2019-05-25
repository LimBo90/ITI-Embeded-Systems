#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MDIO_private.h"

//https://stackoverflow.com/questions/38881877/bit-hack-expanding-bits
//
static u64 MLocal_u64ExpandMask(u16 mask){
	u64 res = 0;
	u64 mask64 = mask;
	res |= (mask64 << 0) & (u64)1;
	res |= (mask64 << 3) & (u64)1 << 4;
	res |= (mask64 << 6) & (u64)1 << 8;
	res |= (mask64 << 9) & (u64)1 << 12;
	res |= (mask64 << 12) & (u64)1 << 16;
	res |= (mask64 << 15) & (u64)1 << 20;
	res |= (mask64 << 18) & (u64)1 << 24;
	res |= (mask64 << 21) & (u64)1 << 28;
	res |= (mask64 << 24) & (u64)1 << 32;
	res |= (mask64 << 27) & (u64)1 << 36;
	res |= (mask64 << 30) & (u64)1 << 40;
	res |= (mask64 << 33) & (u64)1 << 44;
	res |= (mask64 << 36) & (u64)1 << 48;
	res |= (mask64 << 39) & (u64)1 << 52;
	res |= (mask64 << 42) & (u64)1 << 56;
	res |= (mask64 << 45) & (u64)1 << 60;
	res |= res << 1 | res << 2 | res << 3;
	return res;
}


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

void MDIO_voidSetPortMode(u8 Copy_u8Port, u16 Copy_u8Mask, u8 Copy_PinMode){
	u64 Local_u64CRValue;
	u8 Local_u8PullUP = 2;	//not input
	u64 Local_u64Mask = MLocal_u64ExpandMask(Copy_u8Mask);

	if (Copy_PinMode == MDIO_MODE_INPUT_PULLUP || Copy_PinMode == MDIO_MODE_INPUT_PULLDOWN){
		Local_u8PullUP = Copy_PinMode & 1;
		Copy_PinMode >>= 1;
	}

	Local_u64CRValue = (u64)Copy_PinMode;
	Local_u64CRValue |= Local_u64CRValue << 1*4;
	Local_u64CRValue |= Local_u64CRValue << 2*4;
	Local_u64CRValue |= Local_u64CRValue << 4*4;
	Local_u64CRValue |= Local_u64CRValue << 8*4;
	Local_u64CRValue &= Local_u64Mask;
	switch(Copy_u8Port)
	{
		case MDIO_PORTA:
			MDIO_GPIOA->CR &= ~Local_u64Mask ;
			MDIO_GPIOA->CR |=  Local_u64CRValue;
			if(Local_u8PullUP == 0)	//input pull up
				MDIO_GPIOA->ODR &= ~Local_u64Mask ;
			else if(Local_u8PullUP == 1)	//input pull down
				MDIO_GPIOA->ODR |= Local_u64Mask ;
			break;
		case MDIO_PORTB:
			MDIO_GPIOB->CR &= ~Local_u64Mask ;
			MDIO_GPIOB->CR |=  Local_u64CRValue;
			if(Local_u8PullUP == 0)	//input pull up
				MDIO_GPIOB->ODR &= ~Local_u64Mask ;
			else if(Local_u8PullUP == 1)	//input pull down
				MDIO_GPIOB->ODR |= Local_u64Mask ;
			break;
		case MDIO_PORTC:
			MDIO_GPIOC->CR &= ~Local_u64Mask ;
			MDIO_GPIOC->CR |=  Local_u64CRValue;
			if(Local_u8PullUP == 0)	//input pull up
				MDIO_GPIOC->ODR &= ~Local_u64Mask ;
			else if(Local_u8PullUP == 1)	//input pull down
				MDIO_GPIOC->ODR |= Local_u64Mask ;
			break;
		default:
			/* Report Error */
			break;
	}

}
void MDIO_voidSetPortValue(u8 Copy_u8Port, u16 Copy_u8Mask, u16 Copy_u8Value){
	switch(Copy_u8Port){
	case MDIO_PORTA:	MDIO_GPIOA->ODR = (MDIO_GPIOA->ODR & ~Copy_u8Mask) | (Copy_u8Value & Copy_u8Mask);	break;
	case MDIO_PORTB:	MDIO_GPIOB->ODR = (MDIO_GPIOB->ODR & ~Copy_u8Mask) | (Copy_u8Value & Copy_u8Mask);	break;
	case MDIO_PORTC:	MDIO_GPIOC->ODR = (MDIO_GPIOC->ODR & ~Copy_u8Mask) | (Copy_u8Value & Copy_u8Mask);	break;
	default:/* Report Error */																				break;

	}
}
