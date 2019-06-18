#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MTIMER_private.h"
#include "MTIMER_interface.h"
#include "MTIMER_config.h"
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

u32 g_nOverflows, g_preload;

void __vector_11 (void) __attribute__ ((signal, INTR_ATTRS));
void __vector_10 (void) __attribute__ ((signal, INTR_ATTRS));

void (*timer0_OVCallback) (void);
void (* timer0_CompareMatchCallback) (void);

void MTIMER_voidInit(void){
	//Timer0
	//setting mode
	MTIMER0_TCCR0 &= ~(MTIMER0_WGM_MASK);
	MTIMER0_TCCR0 |= MTIMER0_CFG_MODE;


	//enable global interrupts
    SET_BIT(MTIMER_SREG, MTIMER_I);

    //enable timer0 overflow interrupt
    SET_BIT(MTIMER_TIMSK, MTIMER_TOIE0);

    //enable timer0 compare match interrupt
    SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);

    //set prescaler
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
#if MTIMER0_CFG_INITIAL_STATE == MTIMER_INITIAL_STATE_ENABLED
    MTIMER0_TCCR0 |= MTIMER0_CFG_PRESCALER;
#endif
}

void MTIMER_voidSetDesiredTime(u32 Copy_u32Time_ms){
	g_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER0_PRESCALER * 256);
	g_preload = 256 - ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER0_PRESCALER)) % 256;

}

void MTIMER_voidSetCTC(u8 OCR, u32 Copy_u32Time_ms){
	g_nOverflows = (Copy_u32Time_ms * (u64)F_OSC) / (1000 * (u32)MTIMER0_PRESCALER * OCR);
	g_preload = OCR - ((Copy_u32Time_ms * (u64)F_OSC)/(1000 * (u32)MTIMER0_PRESCALER)) % OCR;
	MTIMER0_OCR0 = OCR;

//	HLCD_clearDisplay();
//	HLCD_writeNumber(g_nOverflows);
}


void __vector_11(void){
	static u16 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_nOverflows){
		timer0_OVCallback();
		nOverflows = 0;
		MTIMER0_TCNT0 = g_preload;
	}

}

void __vector_10(void){
	static u16 nOverflows = 0;
	nOverflows++;
	if(nOverflows == g_nOverflows){
		timer0_CompareMatchCallback();
		nOverflows = 0;
	}
}

void MTIMER_voidSetOVCallback(void (*func)(void)){
	timer0_OVCallback = func;
}

void MTIMER_voidSetCompareMatchCallback(void (*func)(void)){
	timer0_CompareMatchCallback = func;
}
void MTIMER_voidStopTimer(void){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
}

void MTIMER_voidStartTimer(void){
    MTIMER0_TCCR0 &= ~MTIMER0_CS_MASK;
    MTIMER0_TCCR0 |= (MTIMER0_CS_MASK & MTIMER0_CFG_PRESCALER);
}

void MTIMER_voidEnableOverflowInterrupt(void){
    SET_BIT(MTIMER_TIMSK, MTIMER_TOIE0);
}

void MTIMER_voidDisableOverflowInterrupt(void){
    CLR_BIT(MTIMER_TIMSK, MTIMER_TOIE0);
}

void MTIMER_voidEnableCompareMatchInterrupt(void){
    SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}

void MTIMER_voidDisableCompareMatchInterrupt(void){
	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}

void MTIMER_voidEnableGlobalInterrupts(void){
    SET_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}

void MTIMER_voidDisableGlobalInterrupts(void){
	CLR_BIT(MTIMER_TIMSK, MTIMER_OCIE0);
}
