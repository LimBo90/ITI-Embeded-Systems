/*
 * main.c
 *
 *  Created on: May 12, 2019
 *      Author: Administrator
 */

#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "HServo_interface.h"
#include "HLCD_interface.h"
#include "util/delay.h"

void printAngle(u8 angle){
	HLCD_clearDisplay();
	HLCD_writeStr("angle = ");
	HLCD_writeNumber(angle);
}

int main(){
	MDIO_setPinDirection(PORTD, PIN_5, OUTPUT);
	HServo_init();
	HLCD_init();
	while(1){
		HServo_rotate(0);
		printAngle(0);
		_delay_ms(500);
		HServo_rotate(90);
		printAngle(90);
		_delay_ms(500);
		HServo_rotate(180);
		printAngle(180);
		_delay_ms(500);
	}
	return 0;
}


