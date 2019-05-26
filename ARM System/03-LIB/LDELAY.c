#include "LSTD_TYPES.h"
#include "LUTILS.h"

static void LUTILS_voidDelay_ms(u16 delay_ms){
	u64 value =  delay_ms * 1000000;
    u64 nLoops = value / 133;
    u64 i;
	for(i=nLoops; i > 0; i--)
		asm("NOP");
	return;
}