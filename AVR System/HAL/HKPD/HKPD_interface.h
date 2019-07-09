#ifndef HKPD_INTERFACE_H_
#define HKPD_INTERFACE_H_



#define HKPD_PORT   PORTA

/**
 * The Keypad pins will be connected to the port as follows
 *
 * 	PIN_0 =====> C4
 * 	PIN_1 =====> C3
 * 	PIN_2 =====> C2
 * 	PIN_3 =====> C1
 * 	PIN_4 =====> R1
 * 	PIN_5 =====> R2
 * 	PIN_6 =====> R3
 * 	PIN_7 =====> R4
 */

#define HKPD_NULL_CHARACTER '\0'
/**
 * Initalizes the keypad
 */
void HKPD_init(void);

/**
 *	Returns 1 if a key is pressed and puts the pressed key in key placeholder provided
 *	Returns 0 if there's no key currently pressed
 */
u8 HKPD_getKey(u8 * key);

#endif
