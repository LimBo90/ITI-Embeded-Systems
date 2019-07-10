/*
 * MADC_private.h
 *
 *  Created on: Jul 9, 2019
 *      Author: Abdelrahman
 */

#ifndef MADC_PRIVATE_H_
#define MADC_PRIVATE_H_

/*********** Registers ****************/
#define MADC_ADMUX 	(*(volatile u8 *) (0x27))
#define MADC_ADCSRA	(*(volatile u8 *) (0x26))
#define MADC_ADC	(*(volatile u16 *) (0x24))

/************ Pins ***************/
//ADMUX
#define MADC_MUX_MASK	0x1F
#define MADC_ADLAR		5
#define MADC_REFS_MASK	0xC0

//ADCSRA
#define MADC_ADPS_MASK	0x07
#define MADC_ADIE		3
#define MADC_ADIF		4
#define MADC_ADATE		5
#define MADC_ADSC		6
#define MADC_ADEN		7

#endif /* MADC_PRIVATE_H_ */
