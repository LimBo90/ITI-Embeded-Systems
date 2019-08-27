#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_


/****************************************/
/*************** GENERAL *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER_TIMSK (*(volatile u8 *) (0x59))
#define MTIMER_TIFR (*(volatile u8 *) (0x58))
#define MTIMER_SREG (*(volatile u8 *) (0x5F))

/*********** PINS *********/
//TIMSK
#define MTIMER_TOIE0	0
#define MTIMER_OCIE0	1
#define MTIMER_TOIE1	2
#define MTIMER_OCIE1B	3
#define MTIMER_OCIE1A	4
#define MTIMER_TICE1	5
#define MTIMER_TOIE2	6
#define MTIMER_OCIE2	7

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
#define MTIMER_I 7

/****************************************/
/*************** TIMER0 *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER_TCCR0 (*(volatile u8 *) (0x53))
#define MTIMER_TCNT0 (*(volatile u8 *) (0x52))
#define MTIMER_OCR0 (*(volatile u8 *) (0x5C))

/*********** PINS *********/
//TCCR0
#define MTIMER_CS_MASK 0x07
#define MTIMER_WGM00	6
#define MTIMER_WGM01	3
#define MTIMER_COM00 4
#define MTIMER_COM01 5
#define MTIMER_FOC0 7


/****************************************/
/*************** TIMER1 *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER_TCCR1A (*(volatile u8 *) (0x4F))
#define MTIMER_TCCR1B (*(volatile u8 *) (0x4E))
#define MTIMER_TCNT1 (*(volatile u16 *) (0x4C))
#define MTIMER_OCR1A (*(volatile u16 *) (0x4A))
#define MTIMER_OCR1B (*(volatile u16 *) (0x48))
#define MTIMER_ICR1 (*(volatile u16 *) (0x46))

/*********** PINS *********/
//TTCR1A
#define MTIMER_WGMA_MASK	0b11
#define MTIMER_FOC1B		2
#define MTIMER_FOC1A		3
#define MTIMER_COM1B0		4
#define MTIMER_COM1B1		5
#define MTIMER_COM1A0		6
#define MTIMER_COM1A1		7

//TTCR1B
#define MTIMER_CS_MASK 		0b111
#define MTIMER_WGMB_MASK	0b00011000
#define MTIMER_ICES1		6
#define MTIMER_ICNC1		7

/****************************************/
/*************** TIMER2 *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER_TCCR2 (*(volatile u8 *) (0x45))
#define MTIMER_TCNT2 (*(volatile u8 *) (0x44))
#define MTIMER_OCR2 (*(volatile u8 *) (0x43))

/*********** PINS *********/
//TCCR2
#define MTIMER_CS_MASK 0x07
#define MTIMER_WGM20	6
#define MTIMER_WGM21	3
#define MTIMER_COM20 4
#define MTIMER_COM21 5
#define MTIMER_FOC2 7

#endif
