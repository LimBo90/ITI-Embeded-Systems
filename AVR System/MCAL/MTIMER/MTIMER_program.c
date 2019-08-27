
#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MTIMER_private.h"
#include "MTIMER_interface.h"
#include "MTIMER_config.h"


#define NULL ((void *)0)

/*** Timer0 Prescaler */
#if MTIMER0_CFG_PRESCALER == MTIMER_PRESCALER_OFF
#define MTIMER0_PRESCALER 1
#elif MTIMER0_CFG_PRESCALER == MTIMER_PRESCALER_8
#define MTIMER0_PRESCALER 8
#elif MTIMER0_CFG_PRESCALER == MTIMER_PRESCALER_64
#define MTIMER0_PRESCALER 64
#elif MTIMER0_CFG_PRESCALER == MTIMER_PRESCALER_256
#define MTIMER0_PRESCALER 256
#elif MTIMER0_CFG_PRESCALER == MTIMER_PRESCALER_1024
#define MTIMER0_PRESCALER 1024
#else
#error "MTIMER0_CFG_PRESCALER configured incorrectly in MTIMER_config.h"
#endif

/*** Timer1 prescaler ***/
#if MTIMER1_CFG_PRESCALER == MTIMER_PRESCALER_OFF
#define MTIMER1_PRESCALER 1
#elif MTIMER1_CFG_PRESCALER == MTIMER_PRESCALER_8
#define MTIMER1_PRESCALER 8
#elif MTIMER1_CFG_PRESCALER == MTIMER_PRESCALER_64
#define MTIMER1_PRESCALER 64
#elif MTIMER1_CFG_PRESCALER == MTIMER_PRESCALER_256
#define MTIMER1_PRESCALER 256
#elif MTIMER1_CFG_PRESCALER == MTIMER_PRESCALER_1024
#define MTIMER1_PRESCALER 1024
#else
#error "MTIMER1_CFG_PRESCALER configured incorrectly in MTIMER_config.h"
#endif

/*** Timer2 prescaler ***/
#if MTIMER2_CFG_PRESCALER == MTIMER_PRESCALER_OFF
#define MTIMER2_PRESCALER 1
#elif MTIMER2_CFG_PRESCALER == MTIMER_PRESCALER_8
#define MTIMER2_PRESCALER 8
#elif MTIMER2_CFG_PRESCALER == MTIMER_PRESCALER_64
#define MTIMER2_PRESCALER 64
#elif MTIMER2_CFG_PRESCALER == MTIMER_PRESCALER_256
#define MTIMER2_PRESCALER 256
#elif MTIMER2_CFG_PRESCALER == MTIMER_PRESCALER_1024
#define MTIMER2_PRESCALER 1024
#else
#error "MTIMER1_CFG_PRESCALER configured incorrectly in MTIMER_config.h"
#endif


u32 g_timer0_nOverflows, g_timer1_nOverflows, g_timer2_nOverflows;
u8 g_timer0_preload, g_timer1_preload, g_timer2_preload;

void __vector_11 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_10 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_9 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_7 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_4 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_5 (void) __attribute__ ((signal, INTR_ATTRS));

/****** Timer0 callbacks *****/
void (*timer0_OVCallback) (void);
void (* timer0_CompareMatchCallback) (void);
void (*timer0_timeLapsedCallback) (void);

/****** Timer1 callbacks *****/
void (*timer1_OVCallback) (void);
void (* timer1_CompareMatchCallback) (void);
void (*timer1_timeLapsedCallback) (void);

/****** Timer2 callbacks *****/
void (*timer2_OVCallback) (void);
void (* timer2_CompareMatchCallback) (void);
void (*timer2_timeLapsedCallback) (void);

void MTIMER_voidInit(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	/*************** Timer0 ****************/
	case MTIMER_TIMER0:
			//setting mode
		#if MTIMER0_CFG_MODE == MTIMER_MODE_NORMAL
			CLR_BIT(MTIMER_TCCR0, MTIMER_WGM00);
			CLR_BIT(MTIMER_TCCR0, MTIMER_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_PHASE_CORRECT_PWM
			SET_BIT(MTIMER_TCCR0, MTIMER_WGM00);
			CLR_BIT(MTIMER_TCCR0, MTIMER_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_CTC
			CLR_BIT(MTIMER_TCCR0, MTIMER_WGM00);
			SET_BIT(MTIMER_TCCR0, MTIMER_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_FAST_PWM
			SET_BIT(MTIMER_TCCR0, MTIMER_WGM00);
			SET_BIT(MTIMER_TCCR0, MTIMER_WGM01);
		#else
		#error	"MTIMER0_CFG_MODE configured incorrectly in MTIMER_config.h"
		#endif
			//set prescaler
			MTIMER_TCCR0 &= ~MTIMER_CS_MASK;
		#if MTIMER0_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
			MTIMER_TCCR0 |= MTIMER_CFG_PRESCALER;
		#elif MTIMER0_CFG_INITIAL_STATE != MTIMER_INITIAL_STATE_DISABLED
		#error "MTIMER0_CFG_INITIAL_STATE configured incorrectly in MTIMER_config.h"
		#endif
			timer0_OVCallback = NULL;
			timer0_CompareMatchCallback = NULL;
			timer0_timeLapsedCallback = NULL;
			break;

	/*************** Timer1 ****************/
	case MTIMER_TIMER1:
			MTIMER_TCCR1A &= ~(MTIMER_WGMA_MASK);
		    MTIMER_TCCR1A |= (MTIMER1_CFG_MODE & MTIMER_WGMA_MASK);
		    MTIMER_TCCR1B &= ~(MTIMER_WGMB_MASK);
		    MTIMER_TCCR1B |= (MTIMER1_CFG_MODE & MTIMER_WGMB_MASK);

		#if MTIMER1_CFG_MODE == MTIMER_MODE_FAST_PWM_14
			CLR_BIT(MTIMER_TCCR1A, MTIMER_COM1A0);
			SET_BIT(MTIMER_TCCR1A, MTIMER_COM1A1);
		#endif
		    //set prescaler
		     MTIMER_TCCR1B &= ~MTIMER_CS_MASK;
		#if MTIMER1_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
		     MTIMER_TCCR1B |= MTIMER_CFG_PRESCALER;
		#elif MTIMER0_CFG_INITIAL_STATE != MTIMER_INITIAL_STATE_DISABLED
		#error "MTIMER1_CFG_INITIAL_STATE configured incorrectly in MTIMER_config.h"
		#endif

			timer1_OVCallback = NULL;
			timer1_CompareMatchCallback = NULL;
			timer1_timeLapsedCallback = NULL;
		     break;

	/*************** Timer2 ****************/
	case MTIMER_TIMER2:
			//setting mode
		#if MTIMER2_CFG_MODE == MTIMER_MODE_NORMAL
			CLR_BIT(MTIMER_TCCR2, MTIMER_WGM20);
			CLR_BIT(MTIMER_TCCR2, MTIMER_WGM21);
		#elif MTIMER2_CFG_MODE == MTIMER_MODE_PHASE_CORRECT_PWM
			SET_BIT(MTIMER_TCCR2, MTIMER_WGM20);
			CLR_BIT(MTIMER_TCCR2, MTIMER_WGM21);
		#elif MTIMER2_CFG_MODE == MTIMER_MODE_CTC
			CLR_BIT(MTIMER_TCCR2, MTIMER_WGM20);
			SET_BIT(MTIMER_TCCR2, MTIMER_WGM21);
		#elif MTIMER2_CFG_MODE == MTIMER_MODE_FAST_PWM
			SET_BIT(MTIMER_TCCR2, MTIMER_WGM20);
			SET_BIT(MTIMER_TCCR2, MTIMER_WGM21);
		#else
		#error	"MTIMER2_CFG_MODE configured incorrectly in MTIMER_config.h"
		#endif
			//set prescaler
			MTIMER_TCCR2 &= ~MTIMER_CS_MASK;
		#if MTIMER2_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
			MTIMER_TCCR2 |= MTIMER_CFG_PRESCALER;
		#elif MTIMER2_CFG_INITIAL_STATE != MTIMER_INITIAL_STATE_DISABLED
		#error "MTIMER2_CFG_INITIAL_STATE configured incorrectly in MTIMER_config.h"
		#endif
			timer2_OVCallback = NULL;
			timer2_CompareMatchCallback = NULL;
			timer2_timeLapsedCallback = NULL;
			break;
	}
}

/**
 * Sets the time after which the the timer will call callback function provided
 * Input :- Copy_u8Timer	MTIMER_TIMER0 or MTIMER_TIMER1
 * 			Copy_u32Ticks	The number of ticks after which the callback function is called
 * 			callBack		The callback function called every Copy_u32Time_ms ms
 */
void MTIMER_voidSetDesiredTime(u8 Copy_u8Timer, u32 Copy_u32Ticks,  void (*callback) (void)){
	u16  rem;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
		g_timer0_nOverflows = Copy_u32Ticks / MTIMER0_MAX_COUNT;
		rem = Copy_u32Ticks % MTIMER0_MAX_COUNT;
		if(rem > 0){
			g_timer0_nOverflows++;
			g_timer0_preload = MTIMER0_MAX_COUNT - rem;
		}else{
			g_timer0_preload = 0;
		}
		MTIMER_TCNT0 = g_timer0_preload;
		timer0_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER1:
		g_timer1_nOverflows = Copy_u32Ticks / MTIMER1_MAX_COUNT;;
		rem = Copy_u32Ticks % MTIMER1_MAX_COUNT;
			if(rem > 0){
				g_timer1_nOverflows++;
				g_timer1_preload = MTIMER1_MAX_COUNT - rem;
			}else{
				g_timer1_preload = 0;
			}
			MTIMER_TCNT1 = g_timer1_preload;
			timer1_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER2:
		g_timer2_nOverflows = Copy_u32Ticks / MTIMER2_MAX_COUNT;
		rem = Copy_u32Ticks % MTIMER2_MAX_COUNT;
		if(rem > 0){
			g_timer2_nOverflows++;
			g_timer2_preload = MTIMER2_MAX_COUNT - rem;
		}else{
			g_timer2_preload = 0;
		}
		MTIMER_TCNT2 = g_timer2_preload;
		timer2_timeLapsedCallback = callback;
		break;
	}
}

/**
 * Sets the time after which the timer will callback function
 * The OCR provided is the value that will be put in OCR register to compare the counter with.
 * Input:
 * 			Copy_u8Timer 		The timer whose CTC mode will be configured (either MTIMER_TIMER0 or MTIMER_TIMER1)
 * 			OCR					The number of ticks after which the the timer will call the callback function provided
 * 			callback			The function called every Copy_u32Time_ms ms
 */
void MTIMER_voidSetDesiredTimeCTC(u8 Copy_u8Timer, u16 Copy_u16OCR, u32 Copy_u32Ticks, void (*callback) (void)){
	u8 Local_u8OCR = (u8)Copy_u16OCR;
	u16 rem;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
		g_timer0_nOverflows = Copy_u32Ticks / Copy_u16OCR;
		rem = Copy_u32Ticks % Copy_u16OCR;
		if(rem > 0){
			g_timer0_nOverflows++;
			g_timer0_preload = Local_u8OCR - rem;
		}else{
			g_timer0_preload = 0;
		}
		MTIMER_OCR0 = Local_u8OCR;
		timer0_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER1:
		g_timer1_nOverflows = Copy_u32Ticks / Copy_u16OCR;
		rem = Copy_u32Ticks % Copy_u16OCR;
		if(rem > 0){
			g_timer1_nOverflows++;
			g_timer1_preload = Copy_u16OCR - rem;
		}else{
			g_timer1_preload = 0;
		}
		MTIMER_OCR1A = Copy_u16OCR;
		timer1_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER2:
		g_timer2_nOverflows = Copy_u32Ticks / Copy_u16OCR;
		rem = Copy_u32Ticks % Copy_u16OCR;
		if(rem > 0){
			g_timer2_nOverflows++;
			g_timer2_preload = Local_u8OCR - rem;
		}else{
			g_timer2_preload = 0;
		}
		MTIMER_OCR2 = Local_u8OCR;
		timer2_timeLapsedCallback = callback;
		break;
	}
}

/**
 * This is available only in timer 1.
 * It enables generating a PWM with variable frequency on OC1A pin
 * Input:	Copy_u32Preiod_ms the period of the PWM in ms signal this will calculate the value that will be put in ICR
 * 			Copy_u8DutyCycle the duty cycle of the pwm range 0 ========> 1000
 * 			if you send 500 that means 50%
 */
void MTIMER_voidSetPwmWithFreq(u32 Copy_u32Preiod_ms, u16 Copy_u8DutyCycle){
	MTIMER_ICR1 = (Copy_u32Preiod_ms * (u64)F_OSC) / (1000 * (u32)MTIMER1_PRESCALER);
	MTIMER_OCR1A = ((u32)Copy_u8DutyCycle * MTIMER_ICR1) / 1000;
}


/*
 * Timer0 Overflow ISR
 */
void __vector_11(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer0_OVCallback != NULL)
		timer0_OVCallback();
	if(nOverflows == g_timer0_nOverflows){
		timer0_timeLapsedCallback();
		nOverflows = 0;
		MTIMER_TCNT0 = g_timer0_preload;
	}
}

/**
 * Timer0 Compare match ISR
 */
void __vector_10(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer0_CompareMatchCallback != NULL)
		timer0_CompareMatchCallback();
	if(nOverflows == g_timer0_nOverflows){
		timer0_timeLapsedCallback();
		MTIMER_TCNT0 = g_timer0_preload;
		nOverflows = 0;
	}
}

/**
 * Timer1 Overflow ISR
 */
void __vector_9(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer1_OVCallback != NULL)
		timer1_OVCallback();
	if(nOverflows == g_timer1_nOverflows){
		timer1_timeLapsedCallback();
		nOverflows = 0;
		MTIMER_TCNT1 = g_timer1_preload;
	}
}

/**
 * Timer1 Compare match ISR
 */
void __vector_7(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer1_CompareMatchCallback != NULL)
		timer1_CompareMatchCallback();
	if(nOverflows == g_timer1_nOverflows){
		timer1_timeLapsedCallback();
		nOverflows = 0;
		MTIMER_TCNT1 = g_timer1_preload;
	}
}

/*
 * Timer2 Overflow ISR
 */
void __vector_5(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer2_OVCallback != NULL)
		timer2_OVCallback();
	if(nOverflows == g_timer2_nOverflows){
		timer2_timeLapsedCallback();
		nOverflows = 0;
		MTIMER_TCNT2 = g_timer2_preload;
	}
}

/**
 * Timer2 Compare match ISR
 */
void __vector_4(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer2_CompareMatchCallback != NULL)
		timer2_CompareMatchCallback();
	if(nOverflows == g_timer2_nOverflows){
		timer2_timeLapsedCallback();
		MTIMER_TCNT2 = g_timer2_preload;
		nOverflows = 0;
	}
}
/**
 * Sets callBack function that's called when the timer reaches the time speciied in setDesiredTime()
 */
void MTIMER_voidSetOVCallback(u8 Copy_u8Timer, void (*func)(void)){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:		timer0_OVCallback = func;	break;
	case MTIMER_TIMER1:		timer1_OVCallback = func;	break;
	case MTIMER_TIMER2:		timer2_OVCallback = func;	break;
	}
}

/**
 * Sets callBack function that's called when the timer reaches the time speciied in setDesiredTimeCTC()
 */
void MTIMER_voidSetCompareMatchCallback(u8 Copy_u8Timer, void (*func)(void)){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:		timer0_CompareMatchCallback = func;	break;
	case MTIMER_TIMER1:		timer1_CompareMatchCallback = func;	break;
	case MTIMER_TIMER2:		timer2_CompareMatchCallback = func;	break;
	}
}

/*
 * Start Timer
 */
void MTIMER_voidStopTimer(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	    MTIMER_TCCR0 &= ~MTIMER_CS_MASK;	break;
	case MTIMER_TIMER1:		MTIMER_TCCR1B &= ~MTIMER_CS_MASK;	break;
	case MTIMER_TIMER2:	    MTIMER_TCCR2 &= ~MTIMER_CS_MASK;	break;
	}
}

/*
 * Stops Timer
 */
void MTIMER_voidStartTimer(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
	    MTIMER_TCCR0 &= ~MTIMER_CS_MASK;
	    MTIMER_TCCR0 |= MTIMER0_CFG_PRESCALER;
	    MTIMER_TCNT0 = g_timer0_preload;
	    break;
	case MTIMER_TIMER1:
		MTIMER_TCCR1B &= ~MTIMER_CS_MASK;
		MTIMER_TCCR1B |= MTIMER0_CFG_PRESCALER;
		MTIMER_TCNT1 = g_timer1_preload;
		break;
	case MTIMER_TIMER2:
	    MTIMER_TCCR2 &= ~MTIMER_CS_MASK;
	    MTIMER_TCCR2 |= MTIMER0_CFG_PRESCALER;
	    MTIMER_TCNT2 = g_timer2_preload;
	    break;
	}
}


void MTIMER_voidEnableOverflowInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE0);	break;
	case MTIMER_TIMER1:	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE1); 	break;
	case MTIMER_TIMER2:	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE2);	break;
	}
}

void MTIMER_voidDisableOverflowInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE0);	break;
	case MTIMER_TIMER1:	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE1); 	break;
	case MTIMER_TIMER2:	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE2); 	break;
	}
}

void MTIMER_voidEnableCompareMatchInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);	break;
	case MTIMER_TIMER1:	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE1A); 	break;
	case MTIMER_TIMER2:	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE2);	break;
	}
}

void MTIMER_voidDisableCompareMatchInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE0);	break;
	case MTIMER_TIMER1:	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE1A); 	break;
	case MTIMER_TIMER2:	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE2);	break;
	}
}

void MTIMER_voidEnableGlobalInterrupts(void){
    SET_BIT(MTIMER_SREG, MTIMER_I);
}

void MTIMER_voidDisableGlobalInterrupts(void){
	CLR_BIT(MTIMER_SREG, MTIMER_I);
}

/**
 * Returns the count (TCNT register)
 */
u16 MTIMER_u16GetCount(u8 Copy_u8Timer){
	u16 res;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	res =  MTIMER_TCNT0; break;
	case MTIMER_TIMER1:	res =  MTIMER_TCNT1; break;
	case MTIMER_TIMER2:	res =  MTIMER_TCNT2; break;
	}
	return res;
}

/**
 * Converts the number of ticks provided to time in ms
 */
u32 MTIMER_u32GetTime_ms(u8 Copy_u8Timer, u32 nTicks){
	u32 res;
	switch(Copy_u8Timer){
		case MTIMER_TIMER0:	res =  ((u64)nTicks * MTIMER0_PRESCALER * 1000)/((u64)F_OSC); break;
		case MTIMER_TIMER1:	res =  ((u64)nTicks * MTIMER1_PRESCALER * 1000)/((u64)F_OSC); break;
		case MTIMER_TIMER2:	res =  ((u64)nTicks * MTIMER2_PRESCALER * 1000)/((u64)F_OSC); break;

	}
	return res;
}

/**
 * Converts the number of ticks provided to time in us
 */
u32 MTIMER_u32GetTime_us(u8 Copy_u8Timer, u32 nTicks){
	u32 res;
	switch(Copy_u8Timer){
		case MTIMER_TIMER0:	res =  ((u64)nTicks * MTIMER0_PRESCALER * 1000000)/((u64)F_OSC); break;
		case MTIMER_TIMER1:	res =  ((u64)nTicks * MTIMER1_PRESCALER * 1000000)/((u64)F_OSC); break;
		case MTIMER_TIMER2:	res =  ((u64)nTicks * MTIMER2_PRESCALER * 1000000)/((u64)F_OSC); break;
	}
	return res;
}

/**
 * Converts the time (in milliseconds) provided to number of ticks
 */
u32 MTIMER_u32GetTicks_ms(u8 Copy_u8Timer, u32 Copy_u32Time_ms){
	u32 nTicks;
	switch (Copy_u8Timer){
		case MTIMER_TIMER0:	nTicks = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER0_PRESCALER);	break;
		case MTIMER_TIMER1:	nTicks = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER1_PRESCALER);	break;
		case MTIMER_TIMER2:	nTicks = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER2_PRESCALER);	break;

	}
	return nTicks;
}

/**
 * Converts the time (in microseconds) provided to number of ticks
 */
u32 MTIMER_u32GetTicks_us(u8 Copy_u8Timer, u32 Copy_u32Time_us){
	u32 nTicks;
	switch (Copy_u8Timer){
		case MTIMER_TIMER0:	nTicks = (Copy_u32Time_us * (u64)F_OSC) / (1000000ULL * (u32)MTIMER0_PRESCALER);	break;
		case MTIMER_TIMER1:	nTicks = (Copy_u32Time_us * (u64)F_OSC) / (1000000ULL * (u32)MTIMER1_PRESCALER);	break;
		case MTIMER_TIMER2:	nTicks = (Copy_u32Time_us * (u64)F_OSC) / (1000000ULL * (u32)MTIMER2_PRESCALER);	break;
	}
	return nTicks;
}
