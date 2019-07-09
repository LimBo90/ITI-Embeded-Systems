/*
 * MICU_config.h
 *
 *  Created on: Jul 5, 2019
 *      Author: Abdelrahman
 */

#ifndef MICU_CONFIG_H_
#define MICU_CONFIG_H_

/***********************************************************************/
/*********** Configurations Values (never change these values) *********/
/***********************************************************************/

//prescaler
#define MICU_PRESCALER_OFF 			0b00000001
#define MICU_PRESCALER_8 			0b00000010
#define MICU_PRESCALER_64 			0b00000011
#define MICU_PRESCALER_256 			0b00000100
#define MICU_PRESCALER_1024 		0b00000101
#define MICU_EXTERNAL_FALLING_EDGE	0b00000110
#define MICU_EXTERNAL_RISING_EDGE 	0b00000111

//noise cancelor
#define MICU_DISABLED   0
#define MICU_ENABLED    1

/**************************************************************************/
/*********************** Configurations ************************************/
/*************************************************************************/


#define F_OSC 8000000UL		// system frequency
#define MICU_CFG_TIMER_PRESCALER    MICU_PRESCALER_8
#define MICU_CFG_NOISE_CANCELOR     MICU_DISABLED

#endif /* MICU_CONFIG_H_ */
