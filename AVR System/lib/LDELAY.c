#include "LSTD_TYPES.h"
#include "LUTILS.h"

#define ONE_LOOP_TIME_ns 133
void LUTILS_voidDelay_ms(u16 delay_ms){
	u64 value =  delay_ms * 1000000;
    u64 nLoops = value / ONE_LOOP_TIME_ns;
    u64 i;
	for(i=nLoops; i > 0; i--)
		asm("NOP");
	return;
}
