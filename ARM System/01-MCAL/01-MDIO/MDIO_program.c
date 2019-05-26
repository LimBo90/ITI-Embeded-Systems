#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_private.h"
#include "MDIO_interface.h"
#include "MDIO_config.h"

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

	#if DIO_U8_PA0_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_0);
		#undef DIO_U8_PA0_MODE
		#define DIO_U8_PA0_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA1_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_1);
		#undef DIO_U8_PA1_MODE
		#define DIO_U8_PA1_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA2_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_2);
		#undef DIO_U8_PA2_MODE
		#define DIO_U8_PA2_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA3_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_3);
		#undef DIO_U8_PA3_MODE
		#define DIO_U8_PA3_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA4_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_4);
		#undef DIO_U8_PA4_MODE
		#define DIO_U8_PA4_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA5_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_5);
		#undef DIO_U8_PA5_MODE
		#define DIO_U8_PA5_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA6_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_6);
		#undef DIO_U8_PA6_MODE
		#define DIO_U8_PA6_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA7_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_7);
		#undef DIO_U8_PA7_MODE
		#define DIO_U8_PA7_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA8_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_8);
		#undef DIO_U8_PA8_MODE
		#define DIO_U8_PA8_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA9_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_9);
		#undef DIO_U8_PA9_MODE
		#define DIO_U8_PA9_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA10_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_10);
		#undef DIO_U8_PA10_MODE
		#define DIO_U8_PA10_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA11_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_11);
		#undef DIO_U8_PA11_MODE
		#define DIO_U8_PA11_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA12_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_12);
		#undef DIO_U8_PA12_MODE
		#define DIO_U8_PA12_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA13_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_13);
		#undef DIO_U8_PA13_MODE
		#define DIO_U8_PA13_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA14_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_14);
		#undef DIO_U8_PA14_MODE
		#define DIO_U8_PA14_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PA15_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOA->ODR, MDIO_PIN_15);
		#undef DIO_U8_PA15_MODE
		#define DIO_U8_PA15_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB0_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_0);
		#undef DIO_U8_PB0_MODE
		#define DIO_U8_PB0_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB1_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_1);
		#undef DIO_U8_PB1_MODE
		#define DIO_U8_PB1_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB2_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_2);
		#undef DIO_U8_PB2_MODE
		#define DIO_U8_PB2_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB3_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_3);
		#undef DIO_U8_PB3_MODE
		#define DIO_U8_PB3_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB4_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_4);
		#undef DIO_U8_PB4_MODE
		#define DIO_U8_PB4_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB5_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_5);
		#undef DIO_U8_PB5_MODE
		#define DIO_U8_PB5_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB6_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_6);
		#undef DIO_U8_PB6_MODE
		#define DIO_U8_PB6_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB7_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_7);
		#undef DIO_U8_PB7_MODE
		#define DIO_U8_PB7_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB8_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_8);
		#undef DIO_U8_PB8_MODE
		#define DIO_U8_PB8_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB9_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_9);
		#undef DIO_U8_PB9_MODE
		#define DIO_U8_PB9_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB10_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_10);
		#undef DIO_U8_PB10_MODE
		#define DIO_U8_PB10_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB11_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_11);
		#undef DIO_U8_PB11_MODE
		#define DIO_U8_PB11_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB12_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_12);
		#undef DIO_U8_PB12_MODE
		#define DIO_U8_PB12_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB13_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_13);
		#undef DIO_U8_PB13_MODE
		#define DIO_U8_PB13_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB14_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_14);
		#undef DIO_U8_PB14_MODE
		#define DIO_U8_PB14_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PB15_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOB->ODR, MDIO_PIN_15);
		#undef DIO_U8_PB15_MODE
		#define DIO_U8_PB15_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PC13_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOC->ODR, MDIO_PIN_13);
		#undef DIO_U8_PC13_MODE
		#define DIO_U8_PC13_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PC14_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOC->ODR, MDIO_PIN_14);
		#undef DIO_U8_PC14_MODE
		#define DIO_U8_PC14_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	
	#if DIO_U8_PC15_MODE == MDIO_MODE_INPUT_PULLUP
		LUTILS_SET_BIT(GPIOC->ODR, MDIO_PIN_15);
		#undef DIO_U8_PC15_MODE
		#define DIO_U8_PC15_MODE MDIO_MODE_INPUT_PULLDOWN
	#endif
	

	MDIO_GPIOA->CR = (u64) (((u64)DIO_U8_PA0_MODE)			|
					 		((u64)DIO_U8_PA1_MODE<<4*1)		|
					 		((u64)DIO_U8_PA2_MODE<<4*2)		|
					 		((u64)DIO_U8_PA3_MODE<<4*3)		|
					 		((u64)DIO_U8_PA4_MODE<<4*4)		|
					 		((u64)DIO_U8_PA5_MODE<<4*5)		|
					 		((u64)DIO_U8_PA6_MODE<<4*6)		|
					 		((u64)DIO_U8_PA7_MODE<<4*7)		|
					 		((u64)DIO_U8_PA8_MODE<<4*8)		|
					 		((u64)DIO_U8_PA9_MODE<<4*9)		|
					 		((u64)DIO_U8_PA10_MODE<<4*10)	|
					 		((u64)DIO_U8_PA11_MODE<<4*11)	|
					 		((u64)DIO_U8_PA12_MODE<<4*12)	|
					 		((u64)DIO_U8_PA13_MODE<<4*13)	|
					 		((u64)DIO_U8_PA14_MODE<<4*14)	|
					 		((u64)DIO_U8_PA15_MODE<<4*15));

	MDIO_GPIOB->CR = (u64) ((u64)(DIO_U8_PB0_MODE)			|
							((u64)DIO_U8_PB1_MODE<<4*1)		|
							((u64)DIO_U8_PB2_MODE<<4*2)		|
							((u64)DIO_U8_PB3_MODE<<4*3)		|
							((u64)DIO_U8_PB4_MODE<<4*4)		|
							((u64)DIO_U8_PB5_MODE<<4*5)		|
							((u64)DIO_U8_PB6_MODE<<4*6)		|
							((u64)DIO_U8_PB7_MODE<<4*7)		|
							((u64)DIO_U8_PB8_MODE<<4*8)		|
							((u64)DIO_U8_PB9_MODE<<4*9)		|
							((u64)DIO_U8_PB10_MODE<<4*10)	|
							((u64)DIO_U8_PB11_MODE<<4*11)	|
							((u64)DIO_U8_PB12_MODE<<4*12)	|
							((u64)DIO_U8_PB13_MODE<<4*13)	|
							((u64)DIO_U8_PB14_MODE<<4*14)	|
							((u64)DIO_U8_PB15_MODE<<4*15));

	MDIO_GPIOC->CR = (u64) (((u64) DIO_U8_PC13_MODE<<4*13)	|
					 		((u64) DIO_U8_PC14_MODE<<4*14)	|
					 		((u64) DIO_U8_PC15_MODE<<4*15));
	MDIO_GPIOA->ODR = 0;
	MDIO_GPIOB->ODR = 0;
	MDIO_GPIOC->ODR = 0;
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
		case MDIO_PORTA:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOA->IDR, Copy_u8Pin)? DIO_U8_HIGH : DIO_U8_LOW;	break;
		case MDIO_PORTB:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOB->IDR, Copy_u8Pin)? DIO_U8_HIGH : DIO_U8_LOW;	break;
		case MDIO_PORTC:	*Copy_u8PinVal = LUTILS_GET_BIT(MDIO_GPIOC->IDR, Copy_u8Pin)? DIO_U8_HIGH : DIO_U8_LOW;	break;
		default: /* Report Error */ 														break;
	}
}

void MDIO_voidSetPinMode(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_PinMode){
	u8 Local_u8PinMode;
	Copy_PinMode &= 0x0F;
	Local_u8PinMode  = Copy_PinMode;

	if (Copy_PinMode == MDIO_MODE_INPUT_PULLDOWN)
		Copy_PinMode = MDIO_MODE_INPUT_PULLUP;

	switch(Copy_u8Port)
	{
		case MDIO_PORTA:
			MDIO_GPIOA->CR &= ~((u64)0x0F << (Copy_u8Pin*4));
			MDIO_GPIOA->CR |=  ((u64)Copy_PinMode << (Copy_u8Pin*4));
			break;
		case MDIO_PORTB:
			MDIO_GPIOB->CR &= (~((u64)0x0F << (Copy_u8Pin*4)));
			MDIO_GPIOB->CR |= ((u64)Copy_PinMode << (Copy_u8Pin*4));
			break;
		case MDIO_PORTC:
			MDIO_GPIOC->CR &= (~((u64)0x0F << (Copy_u8Pin*4)));
			MDIO_GPIOC->CR |= ((u64)Copy_PinMode << (Copy_u8Pin*4));
			break;
		default:
			/* Report Error */
			break;
	}


	if(Local_u8PinMode == MDIO_MODE_INPUT_PULLDOWN){
		switch(Copy_u8Port){
			case MDIO_PORTA:	LUTILS_CLR_BIT(MDIO_GPIOA->ODR, Copy_u8Pin); break;
			case MDIO_PORTB:	LUTILS_CLR_BIT(MDIO_GPIOB->ODR, Copy_u8Pin); break;
			case MDIO_PORTC:	LUTILS_CLR_BIT(MDIO_GPIOC->ODR, Copy_u8Pin); break;
			default:	/* Report Error */									 break;
		}
	}else if(Local_u8PinMode == MDIO_MODE_INPUT_PULLUP){
		switch(Copy_u8Port){
			case MDIO_PORTA:	LUTILS_SET_BIT(MDIO_GPIOA->ODR, Copy_u8Pin); break;
			case MDIO_PORTB:	LUTILS_SET_BIT(MDIO_GPIOB->ODR, Copy_u8Pin); break;
			case MDIO_PORTC:	LUTILS_SET_BIT(MDIO_GPIOC->ODR, Copy_u8Pin); break;
			default:	/* Report Error */									 break;
		}
	}
}

void MDIO_voidSetPortMode(u8 Copy_u8Port, u16 Copy_u16Mask, u8 Copy_PinMode){
	u64 Local_u64CRValue;
	u8 Local_u8PinMode;

	Copy_PinMode &= 0x0F;
	Local_u8PinMode = Copy_PinMode;
	u64 Local_u64Mask = MLocal_u64ExpandMask(Copy_u16Mask);

	// make the 4 mode bits in the pulldown to be 0b1000 as input pullup
	if (Copy_PinMode == MDIO_MODE_INPUT_PULLDOWN)
		Copy_PinMode = MDIO_MODE_INPUT_PULLUP;

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
			break;
		case MDIO_PORTB:
			MDIO_GPIOB->CR &= ~Local_u64Mask ;
			MDIO_GPIOB->CR |=  Local_u64CRValue;
			break;
		case MDIO_PORTC:
			MDIO_GPIOC->CR &= ~Local_u64Mask ;
			MDIO_GPIOC->CR |=  Local_u64CRValue;
			break;
		default:
			/* Report Error */
			break;
	}


	if(Local_u8PinMode == MDIO_MODE_INPUT_PULLDOWN){
		switch(Copy_u8Port){
		case MDIO_PORTA:	MDIO_GPIOA->ODR &= ~Copy_u16Mask ;		break;
		case MDIO_PORTB:	MDIO_GPIOB->ODR &= ~Copy_u16Mask ;		break;
		case MDIO_PORTC:	MDIO_GPIOC->ODR &= ~Copy_u16Mask ;		break;
		default: /*Report Error */									break;
		}
	}else if(Local_u8PinMode == MDIO_MODE_INPUT_PULLUP){
		switch(Copy_u8Port){
		case MDIO_PORTA:	MDIO_GPIOA->ODR |= Copy_u16Mask ;		break;
		case MDIO_PORTB:	MDIO_GPIOB->ODR |= Copy_u16Mask ;		break;
		case MDIO_PORTC:	MDIO_GPIOC->ODR |= Copy_u16Mask ;		break;
		default: /*Report Error */									break;
		}
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
