/*
 * LDelay.c
 *
 *  Created on: Jun 28, 2019
 *      Author: Abdelrahman
 */

#include "LSTD_TYPES.h"
#include "LDelay.h"

#define NLOOPS_IN_1ms ((F_CPU) / 4e3)



 void LDelay_ms(u16 Copy_u16Time_ms){
	while(Copy_u16Time_ms > 0){
		u16 val = NLOOPS_IN_1ms;
		__asm__ volatile (
				"1: sbiw %0,1" "\n\t"
				"brne 1b"
				: "=w" (val)
				: "0" (val)
			);
		Copy_u16Time_ms--;
	}
 }
