#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MTIMER_private.h"
#include "MTIMER_interface.h"
#include "MTIMER_config.h"
#include "HLED_interface.h"
#include "HLCD_interface.h"

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
void (*timer1_OVCallback) (void);
void (* timer1_CompareMatchCallback) (void);

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
		#endif
			break;

	/*************** Timer1 ****************/
	case MTIMER_TIMER1:
			MTIMER1_TCCR1A &= ~(MTIMER1_WGMA_MASK);
		    MTIMER1_TCCR1A |= (MTIMER1_CFG_MODE & MTIMER1_WGMA_MASK);
		    MTIMER1_TCCR1B &= ~(MTIMER1_WGMB_MASK);
		    MTIMER1_TCCR1B |= (MTIMER1_CFG_MODE & MTIMER1_WGMB_MASK);

		    //set prescaler
		     MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;
		 #if MTIMER1_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
		     MTIMER1_TCCR1B |= MTIMER1_CFG_PRESCALER;
		 #endif
		     break;
	}
}

void MTIMER_voidSetDesiredTime(u8 Copy_u8Timer, u32 Copy_u32Time_ms){
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
		break;
	}

}

void displayNumbers(u8 timer){
	switch(timer){
	case MTIMER_TIMER0:
		HLCD_writeNumber(g_timer0_nOverflows);
		HLCD_shiftCursorRight(1);
		HLCD_writeNumber(g_timer0_preload);
		HLCD_shiftCursorRight(1);
		HLCD_writeNumber(MTIMER0_OCR0);
		break;
	case MTIMER_TIMER1:
		HLCD_writeNumber(g_timer1_nOverflows);
		HLCD_shiftCursorRight(1);
		HLCD_writeNumber(g_timer1_preload);
		HLCD_shiftCursorRight(1);
		HLCD_writeNumber(MTIMER1_OCR1A);
		break;
	}
}

void MTIMER_voidSetCTC(u8 Copy_u8Timer, u16 Copy_u16OCR, u32 Copy_u32Time_ms){

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
		MTIMER0_TCNT0 = g_timer0_preload;
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
		MTIMER1_TCNT1 = g_timer1_preload;
		break;
	}
}


void __vector_11(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_timer0_nOverflows){
		timer0_OVCallback();
		nOverflows = 0;
		MTIMER0_TCNT0 = g_timer0_preload;
	}
}

void __vector_10(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_timer0_nOverflows){
		timer0_CompareMatchCallback();
		MTIMER0_TCNT0 = g_timer0_preload;
		nOverflows = 0;
	}
}

void __vector_9(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_timer1_nOverflows){
		timer1_OVCallback();
		nOverflows = 0;
		MTIMER1_TCNT1 = g_timer1_preload;
	}
}

void __vector_7(void){
	static u32 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_timer1_nOverflows){
		timer1_CompareMatchCallback();
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
	    break;
	case MTIMER_TIMER1:
		MTIMER1_TCCR1B &= ~MTIMER1_CS_MASK;
		MTIMER1_TCCR1B |= MTIMER1_CFG_PRESCALER;
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