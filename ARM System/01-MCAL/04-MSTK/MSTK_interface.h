#ifndef _MSTK_INTERFACE_H_
#define _MSTK_INTERFACE_H_

void MSTK_voidInit(void);

void MSTK_voidSetLoadValue(u32 value);

void MSTK_voidSetCallback(void (* callback) (void));

void MSTK_voidStart(void);

#endif
