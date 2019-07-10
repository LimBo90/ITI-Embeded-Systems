/*
 * MADC_config.h
 *
 *  Created on: Jul 9, 2019
 *      Author: Abdelrahman
 */

#ifndef MADC_CONFIG_H_
#define MADC_CONFIG_H_

/***********************************************************************************/
/************	Configurations parameters (dont change these values) ***************/
/***********************************************************************************/
//ADC refrence selection
#define MADC_REF_AREF	0x00
#define MADC_REF_AVCC	0x40
#define MADC_REF_2_65V	0xC0

//ADC Left Adjust Result
#define MADC_RIGHT_ADJUSTED	0
#define MADC_LEFT_ADJUSTED	1

// ADC prescaler selection
#define MADC_PRESCALER_2	0
#define MADC_PRESCALER_4	2
#define MADC_PRESCALER_8	3
#define MADC_PRESCALER_16	4
#define MADC_PRESCALER_32	5
#define MADC_PRESCALER_64	6
#define MADC_PRESCALER_128	7

/************	Configurations	 ***************/
#define MADC_CFG_VOLTAGE_REFRENCE	MADC_REF_AVCC
#define MADC_CFG_RESULT_ADJUSTMENT	MADC_RIGHT_ADJUSTED
#define	MADC_CFG_PRESCALER			MADC_PRESCALER_2


#endif /* MADC_CONFIG_H_ */
