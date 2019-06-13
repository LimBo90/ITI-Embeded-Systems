#ifndef _MUART_PRIVATE_H
#define _MUART_PRIVATE_H_

/***************** Registers ***************/
#define MUART_UDR   *((volatile u8*) 0x2C)
#define MUART_UCSRA *((volatile u8*) 0x2B)
#define MUART_UCSRB *((volatile u8*) 0x2A)
#define MUART_UCSRC *((volatile u8*) 0x40)
#define MUART_UBRRH *((volatile u8*) 0x40)
#define MUART_UBRRL *((volatile u8*) 0x29)

/***************** Pins ***************/
//UCSRA
#define MUART_RXEN  4
#define MUART_RXEN  3

//UCSRB
#define MUART_UCSZ2 2

//UCSRC
#define MUART_UCSZ0 1
#define MUART_UCSZ1 2
#define MUART_UPM0  4
#define MUART_UPM1  5
#define MUART_UMSEL 6

#endif