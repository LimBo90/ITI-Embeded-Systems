#ifndef HKPD_INTERFACE_H_
#define HKPD_INTERFACE_H_

#include "MDIO_interface.h"
#include "HKPD_private.h"


#define HKPD_PORT   PORTA

/**
 * The Keypad pins will be connected to the port as follows
 *
 * 	PIN_0 =====> C1
 * 	PIN_1 =====> C2
 * 	PIN_2 =====> C3
 * 	PIN_3 =====> C4
 * 	PIN_4 =====> R1
 * 	PIN_5 =====> R2
 * 	PIN_6 =====> R3
 * 	PIN_7 =====> R4
 */

#define NULL_CHARACTER '\0'

void HKPD_init(void);
u8 HKPD_getKey(void);

#endif
