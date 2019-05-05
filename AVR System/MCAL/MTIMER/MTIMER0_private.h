#ifndef MTIMER0_PRIVATE_H_
#define MTIMER0_PRIVATE_H_

#include "LSTD_TYPES.h"


/*********** REGISTERS *********/
#define MTIMER0_TCCR0 (*(volatile u8 *) (0x53))
#define MTIMER0_TCNT0 (*(volatile u8 *) (0x52))
#define MTIMER0_OCR0 (*(volatile u8 *) (0x5C))
#define MTIMER0_TIMSK (*(volatile u8 *) (0x59))
#define MTIMER0_TIFR (*(volatile u8 *) (0x58))
#define MTIMER0_SREG (*(volatile u8 *) (0x5F))

/*********** PINS *********/
//TCCR0
#define MTIMER0_CS_MASK 0x07
#define MTIMER0_WGM01 3
#define MTIMER0_COM00 4
#define MTIMER0_COM01 5
#define MTIMER0_WGM00 6
#define MTIMER0_FOC0 7

//TIMSK
#define MTIMER0_OCIE0 1
#define MTIMER0_TOIE0 0

//TIFR
#define MTIMER0_OCF0 1
#define MTIMER0_TOV0 0

//SREG
#define MTIMER0_I 7
#endif
