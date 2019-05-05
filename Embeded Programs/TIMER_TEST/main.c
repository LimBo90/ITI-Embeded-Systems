/*
 * main.c
 *
 *  Created on: May 5, 2019
 *      Author: Administrator
 */

#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "MTIMER0_interface.h"

void toggleLED();

void init(){
	MDIO_setPinDirection(PORTA, PIN_0, OUTPUT);
	MTIMER0_init(MTIMER0_MODE_NORMAL, MTIMER0_PRESCALER_256);
	MTIMER0_enableInterrupt();
	MTIMER0_setDelay(1000);
	MTIMER0_registerISR(toggleLED);
}

int main(){
	init();
	while(1){
//		MDIO_setPinValue(PORTA, PIN_0, HIGH);
//		MTIMER0_delay_ms(1000);
//		MDIO_setPinValue(PORTA, PIN_0, LOW);
//		MTIMER0_delay_ms(1000);
	}
	return 0;
}


void toggleLED(){
	MDIO_togglePin(PORTA, PIN_0);
}
