/*
 * HICU_interface.h
 *
 *  Created on: Jun 25, 2019
 *      Author: Abdelrahman
 */

#ifndef HICU_INTERFACE_H_
#define HICU_INTERFACE_H_


/**
 * Initialize the HICU by intalizing timer 1 and external interrupts
 */
void HICU_voidInit();

/**
 * Returns the period of the PWM in ms
 */
u32 HICU_u32getPreiod_ms();


/**
 * Returns the period of the PWM in microseconds
 */
u32 HICU_u32getPreiod_us();

/**
 * Returns the duty cycle of the PWM
 */
u8 HICU_u8getDutyCycle();

#endif /* HICU_INTERFACE_H_ */
