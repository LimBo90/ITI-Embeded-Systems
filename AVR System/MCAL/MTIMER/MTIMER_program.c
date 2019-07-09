
#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MTIMER_private.h"
#include "MTIMER_interface.h"
#include "MTIMER_config.h"


#define NULL ((void *)0)

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

u32 g_timer0_nOverflows;
u8 g_timer0_preload;
u32 g_timer1_nOverflows;
u16 g_timer1_preload;

void __vector_11 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_10 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_9 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_7 (void) __attribute__ ((signal, INTR_ATTRS));

void (*timer0_OVCallback) (void);
void (* timer0_CompareMatchCallback) (void);
void (*timer0_timeLapsedCallback) (void);

void (*timer1_OVCallback) (void);
void (* timer1_CompareMatchCallback) (void);
void (*timer1_timeLapsedCallback) (void);

void MTIMER_voidInit(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	/*************** Timer0 ****************/
	case MTIMER_TIMER0:
			//setting mode
		#if MTIMER0_CFG_MODE == MTIMER_MODE_NORMAL
			CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
			CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_PHASE_CORRECT_PWM
			SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
			CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_CTC
			CLR_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
			SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
		#elif MTIMER0_CFG_MODE == MTIMER_MODE_FAST_PWM
			SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM00);
			SET_BIT(MTIMER0_TCCR0, MTIMER0_WGM01);
		#else
		#error	"MTIMER0_CFG_MODE configured incorrectly in MTIMER_config.h"
		#endif

			//set prescaler
			MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
		#if MTIMER0_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
			MTIMER0_TCCR0 |= MTIMER0_CFG_PRESCALER;
		#elif MTIMER0_CFG_INITIAL_STATE != MTIMER_INITIAL_STATE_DISABLED
		#error "MTIMER0_CFG_INITIAL_STATE configured incorrectly in MTIMER_config.h"
		#endif
			break;

	/*************** Timer1 ****************/
	case MTIMER_TIMER1:
			MTIMER1_TCCR1A &= ~(MTIMER1_WGMA_MASK);
		    MTIMER1_TCCR1A |= (MTIMER1_CFG_MODE & MTIMER1_WGMA_MASK);
		    MTIMER1_TCCR1B &= ~(MTIMER1_WGMB_MASK);
		    MTIMER1_TCCR1B |= (MTIMER1_CFG_MODE & MTIMER1_WGMB_MASK);

		#if MTIMER1_CFG_MODE == MTIMER_MODE_FAST_PWM_14
			CLR_BIT(MTIMER1_TCCR1A, MTIMER1_COM1A0);
			SET_BIT(MTIMER1_TCCR1A, MTIMER1_COM1A1);
		#endif
		    //set prescaler
		     MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;
		#if MTIMER1_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
		     MTIMER1_TCCR1B |= MTIMER1_CFG_PRESCALER;
		#elif MTIMER0_CFG_INITIAL_STATE != MTIMER_INITIAL_STATE_DISABLED
		#error "MTIMER0_CFG_INITIAL_STATE configured incorrectly in MTIMER_config.h"
		#endif
		     break;
	}
	timer0_OVCallback = NULL;
	timer1_OVCallback = NULL;
	timer0_CompareMatchCallback = NULL;
	timer1_CompareMatchCallback = NULL;
}

void MTIMER_voidSetDesiredTime(u8 Copy_u8Timer, u32 Copy_u32Time_ms,  void (*callback) (void)){
	u16  rem;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:

		g_timer0_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER0_PRESCALER * MTIMER0_MAX_COUNT);
		rem = ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER0_PRESCALER)) % MTIMER0_MAX_COUNT;
		if(rem > 0){
			g_timer0_nOverflows++;
			g_timer0_preload = MTIMER0_MAX_COUNT - rem;
		}else{
			g_timer0_preload = 0;
		}
		MTIMER0_TCNT0 = g_timer0_preload;
		timer0_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER1:
		g_timer1_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER1_PRESCALER * MTIMER1_MAX_COUNT);
		rem = ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER1_PRESCALER)) % MTIMER1_MAX_COUNT;
			if(rem > 0){
				g_timer1_nOverflows++;
				g_timer1_preload = MTIMER1_MAX_COUNT - rem;
			}else{
				g_timer1_preload = 0;
			}
			MTIMER1_TCNT1 = g_timer1_preload;
			timer1_timeLapsedCallback = callback;
		break;
	}
}

void MTIMER_voidSetDesiredTimeCTC(u8 Copy_u8Timer, u16 Copy_u16OCR, u32 Copy_u32Time_ms, void (*callback) (void)){
	u8 Local_u8OCR = (u8)Copy_u16OCR;
	u16 rem;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
		g_timer0_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER0_PRESCALER * Local_u8OCR);
		rem = ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER0_PRESCALER)) % Local_u8OCR;
		if(rem > 0){
			g_timer0_nOverflows++;
			g_timer0_preload = Local_u8OCR - rem;
		}else{
			g_timer0_preload = 0;
		}
		MTIMER0_OCR0 = Local_u8OCR;
		timer0_timeLapsedCallback = callback;
		break;
	case MTIMER_TIMER1:
		g_timer1_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER1_PRESCALER * Copy_u16OCR);
		rem =  ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER1_PRESCALER)) % Copy_u16OCR;
		if(rem > 0){
			g_timer1_nOverflows++;
			g_timer1_preload = Copy_u16OCR - rem;
		}else{
			g_timer1_preload = 0;
		}
		MTIMER1_OCR1A = Copy_u16OCR;
		timer1_timeLapsedCallback = callback;
		break;
	}
}

void MTIMER_voidSetCTC_us(u8 Copy_u8Timer, u16 Copy_u16OCR, u32 Copy_u32Time_us){

	u8 Local_u8OCR = (u8)Copy_u16OCR;
	u16 rem;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
		g_timer0_nOverflows = (Copy_u32Time_us * (u64)F_OSC) / (1000000 * (u64)MTIMER0_PRESCALER * Local_u8OCR);
		rem = ((Copy_u32Time_us * (u64)F_OSC)/(1000000 * (u64)MTIMER0_PRESCALER)) % Local_u8OCR;
		if(rem > 0){
			g_timer0_nOverflows++;
			g_timer0_preload = Local_u8OCR - rem;
		}else{
			g_timer0_preload = 0;
		}
		MTIMER0_OCR0 = Local_u8OCR;
		break;
	case MTIMER_TIMER1:
		g_timer1_nOverflows = (Copy_u32Time_us * (u64)F_OSC) / (1000000 * (u64)MTIMER1_PRESCALER * Copy_u16OCR);
		rem =  ((Copy_u32Time_us * (u64)F_OSC)/(1000000 * (u64)MTIMER1_PRESCALER)) % Copy_u16OCR;
		if(rem > 0){
			g_timer1_nOverflows++;
			g_timer1_preload = Copy_u16OCR - rem;
		}else{
			g_timer1_preload = 0;
		}
		MTIMER1_OCR1A = Copy_u16OCR;
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
	MTIMER1_ICR1 = (Copy_u32Preiod_ms * (u64)F_OSC) / (1000 * (u32)MTIMER1_PRESCALER);
	MTIMER1_OCR1A = ((u32)Copy_u8DutyCycle * MTIMER1_ICR1) / 1000;


}


void __vector_11(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer0_OVCallback != NULL)
		timer0_OVCallback();
	if(nOverflows == g_timer0_nOverflows){
		timer0_timeLapsedCallback();
		nOverflows = 0;
		MTIMER0_TCNT0 = g_timer0_preload;
	}
}

void __vector_10(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer0_CompareMatchCallback != NULL)
		timer0_CompareMatchCallback();
	if(nOverflows == g_timer0_nOverflows){
		timer0_timeLapsedCallback();
		MTIMER0_TCNT0 = g_timer0_preload;
		nOverflows = 0;
	}
}

void __vector_9(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer1_OVCallback != NULL)
		timer1_OVCallback();
	if(nOverflows == g_timer1_nOverflows){
		timer1_timeLapsedCallback();
		nOverflows = 0;
		MTIMER1_TCNT1 = g_timer1_preload;
	}
}

void __vector_7(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(timer1_CompareMatchCallback != NULL)
		timer1_CompareMatchCallback();
	if(nOverflows == g_timer1_nOverflows){
		timer1_timeLapsedCallback();
		nOverflows = 0;
		MTIMER1_TCNT1 = g_timer1_preload;
	}
}

void MTIMER_voidSetOVCallback(u8 Copy_u8Timer, void (*func)(void)){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:		timer0_OVCallback = func;	break;
	case MTIMER_TIMER1:		timer1_OVCallback = func;	break;
	}
}

void MTIMER_voidSetCompareMatchCallback(u8 Copy_u8Timer, void (*func)(void)){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:		timer0_CompareMatchCallback = func;	break;
	case MTIMER_TIMER1:		timer1_CompareMatchCallback = func;	break;
	}
}

void MTIMER_voidStopTimer(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;	break;
	case MTIMER_TIMER1:		MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;	break;
	}
}

void MTIMER_voidStartTimer(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:
	    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
	    MTIMER0_TCCR0 |= MTIMER0_CFG_PRESCALER;
	    MTIMER0_TCNT0 = g_timer0_preload;
	    break;
	case MTIMER_TIMER1:
		MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;
		MTIMER1_TCCR1B |= MTIMER1_CFG_PRESCALER;
		MTIMER1_TCNT1 = g_timer1_preload;
		break;
	}
}

void MTIMER_voidEnableOverflowInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE0);	break;
	case MTIMER_TIMER1:	SET_BIT(MTIMER_TIMSK, MTIMER_TOIE1); 	break;
	}
}

void MTIMER_voidDisableOverflowInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE0);	break;
	case MTIMER_TIMER1:	CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE1); 	break;
	}
}

void MTIMER_voidEnableCompareMatchInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);	break;
	case MTIMER_TIMER1:	SET_BIT(MTIMER_TIMSK, MTIMER_OCIE1A); 	break;
	}
}

void MTIMER_voidDisableCompareMatchInterrupt(u8 Copy_u8Timer){
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE0);	break;
	case MTIMER_TIMER1:	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE1A); 	break;
	}
}

void MTIMER_voidEnableGlobalInterrupts(void){
    SET_BIT(MTIMER_SREG, MTIMER_I);
}

void MTIMER_voidDisableGlobalInterrupts(void){
	CLR_BIT(MTIMER_SREG, MTIMER_I);
}

u16 MTIMER_u16GetCount(u8 Copy_u8Timer){
	u16 res;
	switch(Copy_u8Timer){
	case MTIMER_TIMER0:	res =  MTIMER0_TCNT0; break;
	case MTIMER_TIMER1:	res =  MTIMER1_TCNT1; break;
	}
	return res;
}


u32 MTIMER_u32GetTime_ms(u8 Copy_u8Timer, u32 nTicks){
	u32 res;
	switch(Copy_u8Timer){
		case MTIMER_TIMER0:	res =  ((u64)nTicks * MTIMER0_PRESCALER * 1000)/((u64)F_OSC); break;
		case MTIMER_TIMER1:	res =  ((u64)nTicks * MTIMER1_PRESCALER * 1000)/((u64)F_OSC); break;
	}
	return res;
}

u32 MTIMER_u32GetTime_us(u8 Copy_u8Timer, u32 nTicks){
	u32 res;
	switch(Copy_u8Timer){
		case MTIMER_TIMER0:	res =  ((u64)nTicks * MTIMER0_PRESCALER * 1000000)/((u64)F_OSC); break;
		case MTIMER_TIMER1:	res =  ((u64)nTicks * MTIMER1_PRESCALER * 1000000)/((u64)F_OSC); break;
	}
	return res;
}
