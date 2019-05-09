#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MTIMER0_private.h"
#include "MTIMER0_interface.h"


u8 g_prescaler_timer0 = 0, g_prescaler_timer1 = 0;
volatile u32 g_overflowsCounter, g_overflowsN;
volatile u8 g_rem;
volatile u16 Ton = 0, Toff = 0, T = 0;
void (*TIMER0_ISR_ptr) (void);

void __vector_11(void) __attribute__ ((signal, INTR_ATTRS));
void __vector_10(void) __attribute__ ((signal, INTR_ATTRS));
void __vector_6(void) __attribute__ ((signal, INTR_ATTRS));

void MTIMER0_init(u8 mode, u8 prescaler){
    switch(mode){
        case MTIMER_MODE_NORMAL:
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
        case MTIMER_MODE_PHASE_CORRECT_PWM:
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
        case MTIMER_MODE_CTC:
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            //toggle oc0 on comapre match
            SET_BIT(MTIMER0_TCCR0, MTIMER0_COM00);
            CLR_BIT(MTIMER0_TCCR0, MTIMER0_COM01);

            break;
        case MTIMER_MODE_FAST_PWM:
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
            SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
            break;
    }
    g_prescaler_timer0 = prescaler;
}



void MTIMER1_init(u8 mode, u8 prescaler){
	switch(mode){
	case MTIMER_MODE_NORMAL:
		CLR_BIT(MTIMER1_TCCR1A, MTIMER1_WGM10);
		CLR_BIT(MTIMER1_TCCR1A, MTIMER1_WGM11);
		CLR_BIT(MTIMER1_TCCR1B, MTIMER1_WGM12);
		CLR_BIT(MTIMER1_TCCR1B, MTIMER1_WGM13);
		//detect rising edge
		SET_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1);
		break;
	}
	g_prescaler_timer1 = prescaler;
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
        if(GET_BIT(MTIMER_TIFR, MTIMER_TOV0)){
            overflowsCount--;
           SET_BIT(MTIMER_TIFR, MTIMER_TOV0);
        }
    }
    MTIMER0_TCCR0 &= 0xF8;
}

void MTIMER_enableGlobalInterrupts(){
	SET_BIT(MTIMER_SREG, MTIMER_I);
}

void MTIMER0_enableNormalModeInterrupt(){
	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE0);
}

void MTIMER0_disableNormalModeInterrupt(){
	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE0);
}

void MTIMER0_enableCTCModeInterrupt(){
	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}

void MTIMER0_disableCTCModeInterrupt(){
	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}

void MTIMER1_enableInputCaptureInterrupt(){
	CLR_BIT(MTIMER_TIMSK, MTIMER_TICE1);
}

void MTIMER1_disableInputCaptureInterrupt(){
	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE0);
}

void MTIMER0_setDelay(u32 delay){
//	u8 prescaler = 8;	//hardcoded prescaler 8
//	g_overflowsN = (delay*F_CPU_KHZ)/(256*prescaler);
//	g_rem = ((delay*F_CPU_KHZ)/prescaler)%256;

//	g_overflowsN = (delay*1000) / (256.0);
//	g_rem = (delay * 1000) % (256);

	 g_overflowsN = 3906;
	 g_rem = 64;

    MTIMER0_TCNT0 = 256 - g_rem;
    if(g_rem > 0)
    	g_overflowsN++;
    g_overflowsCounter = g_overflowsN;
}

void MTIMER0_setCompare(u8 OCR, u32 delay){
	u16 prescaler = 1024;
//	double tickTime_ms = (double)prescaler/8000.0;
//	double timeOverflow_ms = tickTime_ms * OCR;
//	double temp = delay/timeOverflow_ms;
//	g_overflowsN = (u32)temp;
//	g_rem = OCR - (temp - g_overflowsN)*OCR;

//    g_overflowsN = ((delay/1000)*F_CPU)/(OCR*prescaler);
//    g_rem = OCR - (((delay/1000)*F_CPU)/(prescaler))%OCR;

    g_overflowsN = 39;
    g_rem = 188;


	if(g_rem > 0){
		g_overflowsN++;
		MTIMER0_TCNT0 = g_rem;
	}else{
		MTIMER0_TCNT0 = 0;
	}

	g_overflowsCounter = g_overflowsN;
}

/**
 * generates a pwm signal on OC0 pin
 * input:	mode	inverted or non-inverted mode
 * 			value 	this value
 * 					in non-inverted mode the duty cycle of PWM will be proportional to value
 * 					in inverted mode the duty cycle of PWM will be inversely proportional to value
 *
 * 					ex:- value = 64
 * 							the duty cycle will be 25% in non-inverted mode
 * 							and will be 75% in inverted mode
 *
 */
void MTIMER0_PWM(u8 mode, u8 value){
	SET_BIT(MTIMER0_TCCR0, MTIMER0_COM01);

	switch(mode){
	case MTIMER0_PWM_MODE_NON_INVERTED:
		CLR_BIT(MTIMER0_TCCR0, MTIMER0_COM00);	break;
	case MTIMER0_PWM_MODE_INVERTED:
		SET_BIT(MTIMER0_TCCR0, MTIMER0_COM00);	break;
	}
	MTIMER0_OCR0 = value;
}

void MTIMER0_registerISR(void (*isr_func)(void)){
	TIMER0_ISR_ptr = isr_func;
}

void __vector_6(void){
	u8 static volatile flag = 0;
	flag++;
	MTIMER1_TCNT1 = 0;
	switch(flag){
	case 1:	//first rising edge
		CLR_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1);
		break;
	case 2:	//first falling edge
		Ton = MTIMER1_ICR1;
		SET_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1);
		break;
	case 3:	//second rising edge
		flag = 1;
		Toff = MTIMER1_ICR1;
		CLR_BIT(MTIMER1_TCCR1B, MTIMER1_ICES1);
		T = Ton + Toff;
		break;
	}
}

void __vector_11(void){
	if(g_overflowsCounter){
		g_overflowsCounter--;
	}else{
		MTIMER0_stopTimer();
		//reset timer values
		g_overflowsCounter = g_overflowsN;
	    MTIMER0_TCNT0 = 256 - g_rem;
		TIMER0_ISR_ptr();
	}
}

void __vector_10(void){
	if(g_overflowsCounter){
		g_overflowsCounter--;
	}else{
		MTIMER0_stopTimer();
		//reset timer values
		g_overflowsCounter = g_overflowsN;
	    MTIMER0_TCNT0 = g_rem;
		TIMER0_ISR_ptr();
	}
}

void MTIMER0_startTimer(){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
    MTIMER0_TCCR0 |= (MTIMER0_CS_MASK & g_prescaler_timer0);
}

void MTIMER1_startTimer(){
    MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;
    MTIMER1_TCCR1B |= (MTIMER1_CS_MASK & g_prescaler_timer1);
}

void MTIMER0_stopTimer(){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
    MTIMER0_TCNT0 = 0;
}

void MTIMER1_stopTimer(){
	MTIMER1_TCCR1B &= ~MTIMER0_CS_MASK;
	MTIMER1_TCCR1B = 0;
}

u16 MTIMER1_getPeriod(){
	return T;
}
u16 MTIMER1_getDutyCycle(){
	return (Ton*100)/T;
}
