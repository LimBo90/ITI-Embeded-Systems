#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "LCBUFFER.h"

#include "MUART_private.h"
#include "MUART_interface.h"
#include "MUART_config.h"

#if MUART_MODE == MUART_MODE_ASYNCH_NORMAL
	#define UBRR  ((F_OSC/(16* (u32)MUART_BAUD_RATE)) - 1)
#elif MUART_MODE == MUART_MODE_ASYNCH_DOUBLE_SPEED
	#define UBRR  ((F_OSC/(8* (u32)MUART_BAUD_RATE)) - 1)
#elif MUART_MODE == MUART_MODE_SYNCH
	#define UBRR  ((F_OSC/(2* (u32)MUART_BAUD_RATE)) - 1)
#else
    #error "error UART mode is not set. set MUART_MODE in MUART_config.h"
#endif


volatile static u8 recieveBuffer;
 static CBuffer sendBuffer;

void (*onReciveCallBack)(u8);

/* Rx complete Interrupt */
void __vector_13 (void) __attribute__ ((signal, INTR_ATTRBS));
/* UDR register empty interrupt */
void __vector_14 (void) __attribute__ ((signal, INTR_ATTRBS));

static void Local_voidEnableUDREmptyInterrupt();
static void Local_voidDisableUDREmptyInterrupt();

/* Enables UDR empty interrupt */
void Local_voidEnableUDREmptyInterrupt(){
	SET_BIT(MUART_UCSRB, MUART_UDRIE);
}

/* Disasble UDR empty interrupt */
void Local_voidDisableUDREmptyInterrupt(){
	CLR_BIT(MUART_UCSRB, MUART_UDRIE);
}

/**
 * Initalizes the UART module
 */
void MUART_voidInit(void){
	u8 Local_u8UCSRC = 0;
    SET_BIT(MUART_UCSRB, MUART_RXEN);    //enable RXEN
    SET_BIT(MUART_UCSRB, MUART_TXEN);    //enable TXEN

    //setting data size
    MUART_UCSRB &= ~MUART_UCSZ2_MASK;
    MUART_UCSRB |= ((u8)MUART_DATA_SIZE >> 2) << 2;

    Local_u8UCSRC |= ((u8)MUART_DATA_SIZE & 0b011) << 1;

    //setting the mode
#if MUART_MODE == MUART_MODE_SYNCH
    CLR_BIT(MUART_UCSRA, MUART_U2X);
    SET_BIT(Local_u8UCSRC, MUART_UMSEL);
#elif MUART_MODE == MUART_MODE_ASYNCH_NORMAL
    CLR_BIT(MUART_UCSRA, MUART_U2X);
    CLR_BIT(Local_u8UCSRC, MUART_UMSEL);
#elif MUART_MODE == MUART_MODE_ASYNCH_DOUBLE_SPEED
    SET_BIT(MUART_UCSRA, MUART_U2X);
    CLR_BIT(Local_u8UCSRC, MUART_UMSEL);
#else
    #error "error UART mode is not set. set MUART_MODE in MUART_config.h"
#endif

    //setting the parity
    Local_u8UCSRC |= MUART_PARITY;

    //sets the stop bit
#if MUART_STOP_BITS == MUART_ONE_STOP_BIT
    CLR_BIT(Local_u8UCSRC, MUART_USBS);    //1 stop bit
#elif MUART_STOP_BITS == MUART_TWO_STOP_BITS
    SET_BIT(Local_u8UCSRC, MUART_USBS);
#else
	#error "error UART stop bits is not set. set MUART_STOP_BITS in MUART_config.h"
#endif

   //setting baud rate
   MUART_UBRRL = (u8) UBRR;
   MUART_UBRRH = UBRR >> 8;

   MUART_UCSRC = (1 << 7) | Local_u8UCSRC;

//enable global interrupts
   SET_BIT(MUART_SREG, MUART_I);

//enable interrupt on recieve
   SET_BIT(MUART_UCSRB, MUART_RXCIE);

  //initalize send circular buffer
   LCBUFFER_voidReset(&sendBuffer);
}

/**
 * Sends a byte through the UART module without polling (character is recorded in buffer and sent when UART is ready to transmit)
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendByte(u8 Copy_u8Data){
	u8 sucess = LCBUFFER_u8Put(&sendBuffer, Copy_u8Data);	/* Put data in buffer */
	if(sucess){	/* if data is put in buffer sucessfully */
		Local_voidEnableUDREmptyInterrupt();	/* enable UDR empty interrupt to begin transmitting when UART is ready */
	}
	return sucess;
}


/**
 * Sends a byte through UART and doesnt return until that character is sent
 */
void MUART_voidSendBytePoling(u8 Copy_u8Data){
	 while(GET_BIT(MUART_UCSRA, MUART_UDRE) == 0);	/* wait until UDR register is empty */
	    MUART_UDR = Copy_u8Data;	/* Tranmit data */
}

/**
 * Sends a string through the UART module
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendStr(u8 *  Copy_u8Data){
	/* puts string into buffer */
	u8 sucess = LCBUFFER_u8PutStr(&sendBuffer, Copy_u8Data);
	if(sucess){/* if string  is put in buffer sucessfully */
		Local_voidEnableUDREmptyInterrupt();	/* enable UDR empty interrupt to begin transmitting when UART is ready */
	}
	return sucess;
}

/**
 * Sends a number through the UART module
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendNumber(u32 n){
	u32 shifter = n;
	u32 i = 1;
	u8 res = 1;
	while(1){
		shifter /= 10;
		if(shifter == 0)
			break;
		i *= 10;
	}
	while(i > 0){
		u8 digit = (n/i) % 10;
		if(!MUART_u8SendByte(digit + '0')){
			res = 0;
			break;
		}
		i  /= 10;
	}
	return res;
}

/**
 * Return 1 if there's a byte received through the UART module if nothing is received returns 0
 * Puts the received byte in Copy_u8Data
 */
u8 MUART_u8RecieveByte(u8 * Copy_u8Data){
	u8 r = 0;
	if(GET_BIT(MUART_UCSRA, MUART_RXC) == 1){ /* if RXC flag is raised (character is recieved) */
		*Copy_u8Data = MUART_UDR;	
		r = 1;
	}
	return r;
}

/**
 * Sets callback that's called when a receive interrupt happens
 */
void MUART_voidSetOnRecieveCallback(void (*func) (u8)){
	onReciveCallBack = func;
}

/* Rx complete ISR (recieve complete) */
void __vector_13(void){
	recieveBuffer = MUART_UDR;	/* record the recieved character */
	onReciveCallBack(recieveBuffer);	/* call the callback function */
}

/* UDR empty ISR (can transmut safely) */
void __vector_14(void){
	u8 c;
	if(LCBUFFER_u8Get(&sendBuffer, &c))	/* get next character from cicular buffer */
		MUART_UDR = c;	/* send that charater */
	else	/* if no more characters in buffer */
		Local_voidDisableUDREmptyInterrupt();	/*disable interrupt which will stop transmitting any more charachters */
}
