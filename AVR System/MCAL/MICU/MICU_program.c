/*
 * MICU_program.c
 *
 *  Created on: Jul 5, 2019
 *      Author: Abdelrahman
 */
#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MICU_private.h"
#include "MICU_config.h"
#include "MICU_interface.h"


#if MICU_CFG_TIMER_PRESCALER ==     MICU_PRESCALER_OFF
#define MICU_PRESCALER 1
#elif MICU_CFG_TIMER_PRESCALER ==   MICU_PRESCALER_8
#define MICU_PRESCALER 8
#elif MICU_CFG_TIMER_PRESCALER ==   MICU_PRESCALER_64
#define MICU_PRESCALER 64
#elif MICU_CFG_TIMER_PRESCALER ==   MICU_PRESCALER_256
#define MICU_PRESCALER 256
#elif MICU_CFG_TIMER_PRESCALER ==   MICU_PRESCALER_1024
#define MICU_PRESCALER 1024
#else
#error "MICU_CFG_TIMER_PRESCALER configured incorrectly in MICU_config.h"
#endif

static volatile u16 n_overflows;    //number of overflows happened after the last capture event
static volatile u32 Ton;
static volatile u32 Toff;

void __vector_6 (void) __attribute__ ((signal, INTR_ATTRS));

void MICU_voidInit(void){
    n_overflows = 0;	
    Ton = 0;
	Toff = 0;

    /* Initalizing Timer1 in normal mode */
	MTIMER1_TCCR1A &= ~(MTIMER1_WGMA_MASK);
	MTIMER1_TCCR1B &= ~(MTIMER1_WGMB_MASK);

    /* Initalize input capture unit */
#if MICU_CFG_NOISE_CANCELOR == MICU_ENABLED
    SET_BIT(MTIMER1_TCCR1B, MTIMER1_ICNC1); //activate noise canceler
#elif MICU_CFG_NOISE_CANCELOR == MICU_DISABLED
    CLR_BIT(MTIMER1_TCCR1B, MTIMER1_ICNC1); //deactivate noise canceler
#else
#error "MICU_CFG_NOISE_CANCELOR configured incorrectly in MICU_config.h it has to be either MICU_ENABLED or MICU_DISABLED"
#endif
    SET_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1); //initially interrupt on rising edge

    /* Enable interrupts */
    SET_BIT(MICU_SREG, MICU_I);             //enable global interrupts
//    SET_BIT(MTIMER_TIMSK, MTIMER_TOIE1);    // enable overflow interrupt
    SET_BIT(MTIMER_TIMSK, MTIMER_TICE1);    // enable input capture interrupt

    //set prescaler and start timer
    MTIMER1_TCCR1B |= MICU_CFG_TIMER_PRESCALER;
}

///* ISR for overflow interrupt */
//void __vector_9(void){
//    n_overflows++;
//}

/* ISR for capture event */
void __vector_6(void){
	static u16 t0 = 0, t1 = 0;
    if(GET_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1)){
        //current edge is rising edge
    	t0 = MTIMER1_ICR1;
		Toff = t0 - t1 ; 	//calculate Toff
        CLR_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1);    //interrupt on falling edge
    }else{
        //current edge is falling edge
		t1 = MTIMER1_ICR1;
		Ton = t1 - t0;
        SET_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1); // interrupt on rising edge
    }
}


u32 MICU_u32getPreiod_ms(){
	u32 nTicks =  Ton + Toff;
	return ((u64)nTicks * MICU_PRESCALER * 1000)/((u64)F_OSC);
}

u8 MICU_u8getDutyCycle(){
	return (Ton * 100UL)/ (Ton + Toff);
}
