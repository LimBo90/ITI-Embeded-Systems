#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MSTK_private.h"
#include "MSTK_interface.h"
#include "MSTK_config.h"


void (*g_systick_callback) (void);

void MSTK_voidInit(){
	LUTILS_SET_BIT(MSTK_CTRL, 1);
	LUTILS_CLR_BIT(MSTK_CTRL, 2);
}

void MSTK_voidSetLoadValue(u32 Copy_u32ReloadValue){
	MSTK_LOAD = Copy_u32ReloadValue;
}

void MSTK_voidSetCallback(void (* callback) (void)){
	g_systick_callback = callback;
}

void MSTK_voidStart(void){
	LUTILS_SET_BIT(MSTK_CTRL, 0);
}


void SysTick_Handler(void){
	g_systick_callback();
}

