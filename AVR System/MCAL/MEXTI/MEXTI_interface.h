#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

#define MEXTI_MODE_LOW_LEVEL 0
#define MEXTI_MODE_LOGICAL_CHANGE 1
#define MEXTI_MODE_FALLING_EDGE 2
#define MEXTI_MODE_RISING_EDGE 3

#define MEXTI_INT0 6
#define MEXTI_INT1 7
#define MEXTI_INT2 5

/**
 * Enables external interrupt
 * Input:-
 * 		INT_no 	which external interrupt to enable, either MEXTI_INT0, MEXTI_INT1 or MEXTI_INT2
 * 		mode	the mode of the external interrupt (controls when an interrupt is triggered)
 * 				either falling edge, rising edge, on change or on low level
 */
void MEXTI_enableINT(u8 INT_no, u8 mode);

/**
 * Disables external interrupt
 * Input:-
 * 		INT_no 	which external interrupt to enable, either MEXTI_INT0, MEXTI_INT1 or MEXTI_INT2
 */
void MEXTI_disableINT(u8 INT_no);

/**
 * Returns the interrupt flag (wither an interrupt is triggered or not).
 * Input:-
 * 		INT_no 	which external interrupt to return its flag
 */
u8 MEXTI_checkINT(u8 INT_no);

/**
 * Sets the callback function of exteranl interrupt
 * Input:-
 * 		INT_no 		which external interrupt to set its callback, either MEXTI_INT0, MEXTI_INT1 or MEXTI_INT2
 *		callback 	the callback function called when an external interrupt happens
 */
void MEXTI_setCallback(u8 INT_no, void(*callback)(void));

/**
 * enable global interrupts
 */
void MEXTI_enableGlobalInterrupts();

/**
 * Disables global interrupts
 */
void MEXTI_disableGlobalInterrupts();

#endif
