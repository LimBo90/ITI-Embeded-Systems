/*
 * MICU_private.h
 *
 *  Created on: Jul 5, 2019
 *      Author: Abdelrahman
 */

#ifndef MICU_PRIVATE_H_
#define MICU_PRIVATE_H_

/*********** REGISTERS *********/
#define MICU_SREG (*(volatile u8 *) (0x5F))
#define MTIMER_TIMSK (*(volatile u8 *) (0x59))
#define MTIMER_TIFR (*(volatile u8 *) (0x58))

/*********** PINS *********/
//TIMSK
#define MTIMER_TOIE1	2
#define MTIMER_TICE1	5

//TIFR
#define MTIMER_TOV0	0
#define MTIMER_OCF0	1
#define MTIMER_TOV1	2
#define MTIMER_OCF1B	3
#define MTIMER_OCF1A	4
#define MTIMER_ICF1	5
#define MTIMER_TOV2 6
#define MTIMER_ICF2 7

//SREG
#define MICU_I 7

/****************************************/
/*************** TIMER1 *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER1_TCCR1A (*(volatile u8 *) (0x4F))
#define MTIMER1_TCCR1B (*(volatile u8 *) (0x4E))
#define MTIMER1_TCNT1 (*(volatile u16 *) (0x4C))
#define MTIMER1_ICR1 (*(volatile u16 *) (0x46))

/*********** PINS *********/
//TTCR1A
#define MTIMER1_WGMA_MASK	0b11

//TTCR1B
#define MTIMER1_CS_MASK 	0b111
#define MTIMER1_WGMB_MASK	0b00011000
#define MTIMER1_ICES1		6
#define MTIMER1_ICNC1		7


/****************************************/
/*************** VALUES *****************/
/****************************************/
#define MTIMER_MAX_COUNT 65536ULL

#endif /* MICU_PRIVATE_H_ */
