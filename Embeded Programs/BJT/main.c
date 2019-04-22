/*
 * main.c
 *
 *  Created on: Apr 17, 2019
 *      Author: Administrator
 */

#include "MDIO_interface.h"
#include "util/delay.h"

#define F_CPU 80000000

int main(){
	MDIO_setPinDirection(PORTC, PIN_7, OUTPUT);

	while(1){
		MDIO_setPinValue(PORTC, PIN_7, HIGH);
		_delay_ms(250);
		MDIO_setPinValue(PORTC, PIN_7, LOW);
		_delay_ms(250);
	}
	return 0;
}
