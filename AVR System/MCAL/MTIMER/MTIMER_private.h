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
#define MTIMER0_TCCR0 (*(volatile u8 *) (0x53))
#define MTIMER0_TCNT0 (*(volatile u8 *) (0x52))
#define MTIMER0_OCR0 (*(volatile u8 *) (0x5C))

/*********** PINS *********/
//TCCR0
#define MTIMER0_CS_MASK 0x07
#define MTIMER0_WGM_MASK 0b01001000
#define MTIMER0_COM00 4
#define MTIMER0_COM01 5
#define MTIMER0_FOC0 7


/****************************************/
/*************** TIMER1 *****************/
/****************************************/

/*********** REGISTERS *********/
#define MTIMER1_TCCR1A (*(volatile u8 *) (0x4F))
#define MTIMER1_TCCR1B (*(volatile u8 *) (0x4E))
#define MTIMER1_TCNT1 (*(volatile u16 *) (0x4C))
#define MTIMER1_OCR1A (*(volatile u16 *) (0x4A))
#define MTIMER1_OCR1B (*(volatile u16 *) (0x48))
#define MTIMER1_ICR1 (*(volatile u16 *) (0x46))

/*********** PINS *********/
//TTCR1A
#define MTIMER1_WGM10	0
#define MTIMER1_WGM11	1
#define MTIMER1_FOC1B	2
#define MTIMER1_FOC1A	3
#define MTIMER1_COM1B0	4
#define MTIMER1_COM1B1	5
#define MTIMER1_COM1A0	6
#define MTIMER1_COM1A1	7

//TTCR1B
#define MTIMER1_CS_MASK 0x07
#define MTIMER1_WGM12	3
#define MTIMER1_WGM13	4
#define MTIMER1_ICES1	6
#define MTIMER1_ICNC1	7

#endif
