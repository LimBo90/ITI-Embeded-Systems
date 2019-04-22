#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

#include "LSTD_TYPES.h"


#define MEXTI_MODE_LOW_LEVEL 0
#define MEXTI_MODE_LOGICAL_CHANGE 1
#define MEXTI_MODE_FALLING_EDGE 2
#define MEXTI_MODE_RISING_EDGE 3

#define MEXTI_INT0 6
#define MEXTI_INT1 7
#define MEXTI_INT2 5

void MEXTI_enableINT(u8 INT_no, u8 mode);
void MEXTI_disableINT(u8 INT_no);
u8 MEXTI_checkINT(u8 INT_no);
void MEXTI_registerISR(u8 INT_no, void(*ptr)(void));
void MEXTI_enableInterrupts();
void MEXTI_disableInterrupts();

#endif
