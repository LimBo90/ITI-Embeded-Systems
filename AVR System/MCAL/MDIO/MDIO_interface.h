#ifndef MDIO_INTERFACE_H_
#define MDIO_INTERFACE_H_

#define INPUT 1
#define OUTPUT 2
#define INPUT_PULLUP 3
#define INPUT_PULLDOWN 4

#define LOW 0
#define HIGH 1

#define PORTA 1
#define PORTB 2
#define PORTC 3
#define PORTD 4

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_private.h"

void MDIO_setPinDirection(u8 port, u8 pin, u8 direction);
void MDIO_setPinValue(u8 port, u8 pin, u8 value);
u8 MDIO_getPinValue(u8 port, u8 pin);
void MDIO_togglePin(u8 port, u8 pin);
void MDIO_setPortDirection(u8 port, u8 mask, u8 direction);
void MDIO_setPort(u8 port, u8 mask);
void MDIO_clrPort(u8 port, u8 mask);
void MDIO_setPortToValue(u8 port, u8 mask, u8 value);
u8 MDIO_getPortValue(u8 port, u8 mask);

#endif
