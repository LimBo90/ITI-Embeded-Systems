#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MUART_private.h"
#include "MUART_interface.h"
#include "MUART_config.h"
#include "HLCD_interface.h"

#if MUART_MODE == MUART_MODE_ASYNCH_NORMAL
	#define UBRR  (F_OSC/(16* (u32)MUART_BAUD_RATE)) - 1
#elif MUART_MODE == MUART_MODE_ASYNCH_DOUBLE_SPEED
	#define UBRR  (F_OSC/(8* (u32)MUART_BAUD_RATE)) - 1
#elif MUART_MODE == MUART_MODE_SYNCH
	#define UBRR  (F_OSC/(2* (u32)MUART_BAUD_RATE)) - 1
#else
    #error "error UART mode is not set. set MUART_MODE in MUART_config.h"
#endif

static u8 Global_u8RecieveBuffer[RECIEVE_BUFFER_SIZE] = {'\0'};
volatile static u32 Global_u32ReciveBufferSize = 0;
volatile static u8 buffer;

void __vector_13 (void) __attribute__ ((signal, INTR_ATTRBS));

void MUART_voidInit(void){
    SET_BIT(MUART_UCSRB, MUART_RXEN);    //enable RXEN
    SET_BIT(MUART_UCSRB, MUART_TXEN);    //enable TXEN

    //setting data size
    MUART_UCSRC &= ~MUART_UCSZ_MASK;
    MUART_UCSRC |= ((u8)MUART_DATA_SIZE << 5) >> 2;
    MUART_UCSRB &= ~MUART_UCSZ2_MASK;
    MUART_UCSRB |= ((u8)MUART_DATA_SIZE >> 2) << 2;

    //setting the mode
#if MUART_MODE == MUART_MODE_SYNCH
    CLR_BIT(MUART_UCSRA, MUART_U2X);
    SET_BIT(MUART_UCSRC, MUART_UMSEL);
#elif MUART_MODE == MUART_MODE_ASYNCH_NORMAL
    CLR_BIT(MUART_UCSRA, MUART_U2X);
    CLR_BIT(MUART_UCSRC, MUART_UMSEL);
#elif MUART_MODE == MUART_MODE_ASYNCH_DOUBLE_SPEED
    SET_BIT(MUART_UCSRA, MUART_U2X);
    CLR_BIT(MUART_UCSRC, MUART_UMSEL);
#else
    #error "error UART mode is not set. set MUART_MODE in MUART_config.h"
#endif

    //setting the parity
    MUART_UCSRC &= ~MUART_PARITY_BITS_MASK;
    MUART_UCSRC |= MUART_MODE;

    //sets the stop bit
#if MUART_STOP_BITS == MUART_ONE_STOP_BIT
    CLR_BIT(MUART_UCSRC, MUART_USBS);    //1 stop bit
#elif MUART_STOP_BITS == MUART_TWO_STOP_BITS
    SET_BIT(MUART_UCSRC, MUART_USBS);
#else
	#error "error UART stop bits is not set. set MUART_STOP_BITS in MUART_config.h"
#endif

   //settig baud rate
   MUART_UBRRL = (u8) UBRR;
   MUART_UBRRH = (UBRR >> 8);

   //enable global interrupts
   SET_BIT(MUART_SREG, MUART_I);

//   enable interrupt on recieve
   SET_BIT(MUART_UCSRB, MUART_RXCIE);

}

void MUART_voidSendByte(u8 Copy_u8Data){
    while(GET_BIT(MUART_UCSRA, MUART_UDRE) == 0);
    MUART_UDR = Copy_u8Data;
}

u8 MUART_voidRecieveByte(u8 * Copy_u8Data){
//	if(GET_BIT(MUART_UCSRA, MUART_RXC) == 1){
//		*Copy_u8Data = MUART_UDR;
//		return 1;
//	}else{
//		return 0;
//	}
	if(Global_u32ReciveBufferSize){
		*Copy_u8Data = buffer;
		Global_u32ReciveBufferSize = 0;
		return 1;
	}else{
		return 0;
	}
}

void __vector_13(void){
	buffer = MUART_UDR;
	Global_u32ReciveBufferSize = 1;
}
