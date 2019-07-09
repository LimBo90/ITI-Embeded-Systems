/*
 * MICU_interface.h
 *
 *  Created on: Jul 5, 2019
 *      Author: Abdelrahman
 */

#ifndef MICU_INTERFACE_H_
#define MICU_INTERFACE_H_



/**
 * Initializes the input capture unit
 */
void MICU_voidInit(void);

/**
 * Returns the period of the PWM in microseconds
 */
u32 MICU_u32getPreiod_ms();

/**
 * Returns the duty cycle of the PWM
 */
u8 MICU_u8getDutyCycle();

#endif /* MICU_INTERFACE_H_ */
