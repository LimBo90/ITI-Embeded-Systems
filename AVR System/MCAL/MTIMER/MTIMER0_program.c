

#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MTIMER0_private.h"
#include "MTIMER0_interface.h"


u8 g_prescaler = 0;
volatile u32 g_overflowsCounter, g_overflowsN;
volatile u8 g_rem;

void (*TIMER0_ISR_ptr) (void);

void __vector_11(void) __attribute__ ((signal, INTR_ATTRS));
void startTimer(void);

void MTIMER0_init(u8 mode, u8 prescaler){
    switch(mode){
        case MTIMER0_MODE_NORMAL:
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
        case MTIMER0_MODE_PWM:
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
        case MTIMER0_MODE_CTC:
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
        case MTIMER0_MODE_FAST_PWM:
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
    }
    g_prescaler = prescaler;
}


void MTIMER0_delay_ms(u32 delay){
    //u8 prescaler = 8;
    // u32 overflowsCount = delay*F_CPU/(256*prescaler*1000);
    // u8 rem = (delay*F_CPU/(prescaler*1000))%256

    u32 overflowsCount = (delay*1000) / 256;
    u8 rem = (delay * 1000) % 256;
    MTIMER0_TCNT0 = 0;
    if(rem > 0){
        MTIMER0_TCNT0 = 256 - rem;
        overflowsCount++;
    }
    MTIMER0_TCCR0 = (MTIMER0_TCCR0 & 0xF8) | 0x02;
    while(overflowsCount != 0){
        if(GET_BIT(MTIMER0_TIFR, MTIMER0_TOV0)){
            overflowsCount--;
           SET_BIT(MTIMER0_TIFR, MTIMER0_TOV0);
        }
    }
    MTIMER0_TCCR0 &= 0xF8;
}



void MTIMER0_enableInterrupt(){
	SET_BIT(MTIMER0_SREG, MTIMER0_I);
	SET_BIT(MTIMER0_TIMSK, MTIMER0_TOIE0);
}

void MTIMER0_disableInterrupt(){
	CLR_BIT(MTIMER0_TIMSK, MTIMER0_TOIE0);
}

void MTIMER0_setDelay(u32 delay){
	g_overflowsN = (delay*1000) / 256;
    g_rem = (delay * 1000) % 256;
    MTIMER0_TCNT0 = 256 - g_rem;
    if(g_rem > 0)
    	g_overflowsN++;

    g_overflowsCounter = g_overflowsN;
    MTIMER0_startTimer();
}

void MTIMER0_registerISR(void (*isr_func)(void)){
	TIMER0_ISR_ptr = isr_func;
}

void __vector_11(void){
	if(g_overflowsCounter){
		g_overflowsCounter--;
	}else{
		TIMER0_ISR_ptr();
		//resets timer
		g_overflowsCounter = g_overflowsN;
		MTIMER0_TCNT0 = 256 - g_rem;
	}
}

void MTIMER0_startTimer(){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
    MTIMER0_TCCR0 |= (MTIMER0_CS_MASK & g_prescaler);
}

void MTIMER0_stopTimer(){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
    MTIMER0_TCNT0 = 0;
}
