/*
 * HICU_program.c
 *
 *  Created on: Jun 25, 2019
 *      Author: Abdelrahman
 */
#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MEXTI_interface.h"
#include "MTIMER_interface.h"
#include "HICU_interface.h"
#include "HICU_config.h"
#include "HICU_private.h"

typedef enum {Rising, Falling} Edge;

volatile u32 Ton;
volatile u32 Toff;
volatile u32 n_overflows;

void HICU_voidInit(){
	//initalizing timer 1
	MTIMER_voidInit(HICU_TIMER);
	MTIMER_voidEnableOverflowInterrupt(HICU_TIMER);
	MTIMER_voidSetOVCallback(HICU_TIMER, HICU_voidCountOverflows);
	MTIMER_voidStartTimer(HICU_TIMER);

	// initalizing external interrupt

#if HICU_CFG_EXTI == HICU_EXTI0
	MDIO_setPinDirection(PORTD, PIN_2, INPUT_PULLUP);
#elif HICU_CFG_EXTI == HICU_EXTI1
	MDIO_setPinDirection(PORTD, PIN_3, INPUT_PULLUP);
#elif HICU_CFG_EXTI == HICU_EXTI2
	MDIO_setPinDirection(PORTB, PIN_2, INPUT_PULLUP);
#else
	#error "HICU_EXTI configured incorrectly in HICU_config.h"
#endif

	MEXTI_enableGlobalInterrupts();
	MEXTI_setCallback(HICU_EXTI, HICU_voidMeasurePWM);
	MEXTI_enableINT(HICU_EXTI, MEXTI_MODE_FALLING_EDGE);

	//Initalize globals
	Ton = 0;
	Toff = 0;
	n_overflows = 0;
}

void HICU_voidMeasurePWM(){
	u16 time = MTIMER_u16GetCount(HICU_TIMER);
	static Edge currentEdge = Falling;
	static u16 t0 = 0, t1 = 0;
	if(currentEdge  == Rising){
		t0 = time;
		Toff = t0 + n_overflows * HICU_TIMER_MAX_COUNT - t1 ;
		n_overflows = 0;
		MEXTI_enableINT(HICU_EXTI, MEXTI_MODE_FALLING_EDGE);
		currentEdge = Falling;
	}else if(currentEdge == Falling){
		t1 = time;
		Ton = t1 + n_overflows * HICU_TIMER_MAX_COUNT - t0;
		n_overflows = 0;
		MEXTI_enableINT(HICU_EXTI, MEXTI_MODE_RISING_EDGE);
		currentEdge = Rising;
	}
}

u32 HICU_u32getPreiod_ms(){
	u32 nTicksPerPeriod = Ton + Toff;
	return MTIMER_u32GetTime_ms(HICU_TIMER, nTicksPerPeriod);
}

u32 HICU_u32getPreiod_us(){
	u32 nTicksPerPeriod = Ton + Toff;
	return MTIMER_u32GetTime_us(HICU_TIMER, nTicksPerPeriod);
}

u8 HICU_u8getDutyCycle(){
	return (Ton * 100UL)/ (Ton + Toff);
}

void HICU_voidCountOverflows(){
	n_overflows++;
}
