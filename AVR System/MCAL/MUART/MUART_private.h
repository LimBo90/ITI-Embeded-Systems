#ifndef _MUART_PRIVATE_H
#define _MUART_PRIVATE_H_

/***************** Registers ***************/
#define MUART_UDR   *((volatile u8*) 0x2C)
#define MUART_UCSRA *((volatile u8*) 0x2B)
#define MUART_UCSRB *((volatile u8*) 0x2A)
#define MUART_UCSRC *((volatile u8*) 0x40)
#define MUART_UBRRH *((volatile u8*) 0x40)
#define MUART_UBRRL *((volatile u8*) 0x29)
#define MUART_SREG (*(volatile u8 *) (0x5F))


/***************** Pins ***************/
//UCSRA
#define MUART_MPCM 0
#define MUART_U2X 1
#define MUART_PE 2
#define MUART_DOR 3
#define MUART_FE 4
#define MUART_UDRE 5
#define MUART_TXC 6
#define MUART_RXC 7

//UCSRB
#define MUART_TXB8 0
#define MUART_RXB8 1
#define MUART_UCSZ2_MASK 0x02;
#define MUART_TXEN  3
#define MUART_RXEN  4
#define MUART_UDRIE 5
#define MUART_TXCIE 6
#define MUART_RXCIE 7


//UCSRC
#define MUART_UCPOL 0
#define MUART_UCSZ_MASK 0x30
#define MUART_USBS 	3
#define MUART_UPM0  4
#define MUART_UPM1  5
#define MUART_UMSEL 6
#define MUART_URSEL 7

//SREG
#define MUART_I 7
/************** Configuration ***********/
//mode
#define MUART_MODE_ASYNCH_NORMAL		0
#define MUART_MODE_SYNCH				1
#define MUART_MODE_ASYNCH_DOUBLE_SPEED	2

//data size
#define MUART_DATA_SIZE_9	0b111
#define MUART_DATA_SIZE_8	0b011
#define MUART_DATA_SIZE_7	0b010
#define MUART_DATA_SIZE_6	0b001
#define MUART_DATA_SIZE_5	0b000

//stop bits
#define MUART_ONE_STOP_BIT 	0
#define MUART_TWO_STOP_BITS 1

//parity bit
#define MUART_PARITY_DISABLE 	0b00000000
#define MUART_PARITY_EVEN 		0b00100000
#define MUART_PARITY_ODD 		0b00110000
#define MUART_PARITY_BITS_MASK 	0b00110000

#endif
