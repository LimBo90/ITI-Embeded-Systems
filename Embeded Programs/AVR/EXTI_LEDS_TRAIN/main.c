/*
 * main.c
 *
 *  Created on: Apr 22, 2019
 *      Author: Administrator
 */
#define F_CPU 8000000
#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "util/delay.h"

#include "HLED_interface.h"
#include "MDIO_interface.h"
#include "MEXTI_interface.h"

#define LEDS_PORT PORTA
void toggleAllLEDS();

int main(){
	HLED_initLEDS(LEDS_PORT, 0xFF);
	MDIO_setPinDirection(PORTD, PIN_2, INPUT_PULLUP);
	MEXTI_enableInterrupts();
	MEXTI_enableINT(MEXTI_INT0, MEXTI_MODE_LOGICAL_CHANGE);
	MEXTI_registerISR(MEXTI_INT0, toggleAllLEDS);
	u8 i = 0;
	while(1){
		HLED_on(LEDS_PORT, i);
		_delay_ms(500);
		HLED_off(LEDS_PORT, i);
		i++;
		if(i == 8)
			i = 0;
	}
	return 0;
}


void toggleAllLEDS(){
	u8 temp = MDIO_getPortValue(LEDS_PORT, 0xFF);
	MDIO_setPortToValue(LEDS_PORT, 0xFF, 0xFF);
	_delay_ms(1000);
	MDIO_setPortToValue(LEDS_PORT, 0xFF, 0);
	_delay_ms(1000);
	MDIO_setPortToValue(LEDS_PORT, 0xFF, temp);
}
