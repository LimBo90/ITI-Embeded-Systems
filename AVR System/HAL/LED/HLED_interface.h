#ifndef HLED_INTERFACE_H_
#define HLED_INTERFACE_H_

#include "LSTD_TYPES.h"
#include "LUTILS.h"

void HLED_init(u8 port, u8 pin);
void HLED_initLEDS(u8 port, u8 mask);
void HLED_on(u8 port, u8 pin);
void HLED_off(u8 port, u8 pin);
void HLED_toggle(u8 port, u8 pin);

#endif
