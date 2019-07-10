/*
 * MADC_program.c
 *
 *  Created on: Jul 9, 2019
 *      Author: Abdelrahman
 */
#include "LUTILS.h"
#include "LSTD_TYPES.h"

#include "MUART_interface.h"

#include "MADC_private.h"
#include "MADC_config.h"
#include "MADC_interface.h"


void (*conversionFinishedCallback)(u16);

void __vector_16 (void)__attribute__((signal,INTR_ATTRS));

void MADC_voidInit(void){
// select result adjustment (left or right adjusted)
#if MADC_CFG_RESULT_ADJUSTMENT	== MADC_LEFT_ADJUSTED
	SET_BIT(MADC_ADMUX, MADC_ADLAR);
#elif MADC_CFG_RESULT_ADJUSTMENT == MADC_RIGHT_ADJUSTED
	CLR_BIT(MADC_ADMUX, MADC_ADLAR);
#else
#error "MADC_CFG_RESULT_ADJUSTMENT not configured properly in MADC_config.h it can either be MADC_LEFT_ADJUSTED or MADC_RIGHT_ADJUSTED"
#endif

// select voltage refrenece for ADC
	MADC_ADMUX &= ~(MADC_REFS_MASK);
	MADC_ADMUX |= MADC_CFG_VOLTAGE_REFRENCE;

// select prescaler
	MADC_ADCSRA &= ~(MADC_ADPS_MASK);
	MADC_ADCSRA |= MADC_CFG_PRESCALER;

// enable ADC
	SET_BIT(MADC_ADCSRA, MADC_ADEN);
}



void MADC_voidSetChannel(u8 channel){
	MADC_ADMUX &= ~(MADC_MUX_MASK);
	MADC_ADMUX |= channel;
}

u16 MADC_voidStartConversionSynch(void){
	SET_BIT(MADC_ADCSRA, MADC_ADSC);	//start conversion

	while(GET_BIT(MADC_ADCSRA, MADC_ADSC));// wait until conversion finishes

	//return result
#if MADC_CFG_RESULT_ADJUSTMENT == MADC_LEFT_ADJUSTED
	return (MADC_ADC >> 6); //if result is left adjusted shift it
#elif MADC_CFG_RESULT_ADJUSTMENT == MADC_RIGHT_ADJUSTED
	return (MADC_ADC & 0x03FF);	//if result is right adjusted mask highest 6 bits
#endif
}



void MADC_voidStartConversionAsynch(void (*callBack)(u16)){
	conversionFinishedCallback = callBack;
	SET_BIT(MADC_ADCSRA, MADC_ADIE); 	//enable conversion finished interrupt
	SET_BIT(MADC_ADCSRA, MADC_ADSC);	//start conversion

}


void __vector_16 (void){
	u16  res;
#if MADC_CFG_RESULT_ADJUSTMENT == MADC_LEFT_ADJUSTED
	res = (MADC_ADC >> 6); //if result is left adjusted shift it
#elif MADC_CFG_RESULT_ADJUSTMENT == MADC_RIGHT_ADJUSTED
	res = (MADC_ADC & 0x03FF);	//if result is right adjusted mask highest 6 bits
#endif
	conversionFinishedCallback(res);
//	CLR_BIT(MADC_ADCSRA, MADC_ADIE;	//disable conversion finished interrupt
}
