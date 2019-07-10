/*
 * MADC_interface.h
 *
 *  Created on: Jul 9, 2019
 *      Author: Abdelrahman
 */

#ifndef MADC_INTERFACE_H_
#define MADC_INTERFACE_H_


//channel selection
#define MADC_ADC0	0
#define MADC_ADC1	1
#define MADC_ADC2	2
#define MADC_ADC3	3
#define MADC_ADC4	4
#define MADC_ADC5	5
#define MADC_ADC6	6
#define MADC_ADC7	7

/**
 * Initializes ADC peripheral
 */
void MADC_voidInit(void);

/**
 * Sets which ADC channel the ADC uses to convert
 */
void MADC_voidSetChannel(u8 channel);

/**
 * Converts analog signal and blocks CPU until conversion is finished then returns the result
 */
u16 MADC_voidStartConversionSynch(void);

/**
 * Converts analog signal and calls the callback function provided when conversion finishes
 */
void MADC_voidStartConversionAsynch(void (*callBack)(u16));

#endif /* MADC_INTERFACE_H_ */
