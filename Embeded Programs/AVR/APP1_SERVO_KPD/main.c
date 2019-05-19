/*
 * main.c
 *
 *  Created on: May 13, 2019
 *      Author: Administrator
 */


#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "HKPD_interface.h"
#include "HLCD_interface.h"
#include "HServo_interface.h"
#include "util/delay.h"

u64 getNumber(){
	u64 res = 0;
	u8 c = HKPD_getKey();
	while(c != 'K'){
		HLCD_writeData(c);
		res = (res*10) + (c - '0');
		c = HKPD_getKey();
	}
	return res;
}

void init(){
	HLCD_init();
	HKPD_init();
	HServo_init();
	MDIO_setPinDirection(PORTD, PIN_5, OUTPUT);
}

void displayPosition(u8 angle){
	HLCD_clearDisplay();
	HLCD_writeStr("Position: ");
	HLCD_writeNumber(angle);
}

void displayPrompt(u8 str[]){
	HLCD_setCursor(1,0);
	HLCD_writeStr(str);
}

int main(){
	init();
	displayPosition(0);
	displayPrompt("input: ");
	u8 angle = 0;
	while(1){
		u16 inputAngle = getNumber();
		if(inputAngle < 0 || inputAngle > 180){
			displayPrompt("Invalid Angle");
			_delay_ms(2000);
		}else{
			HServo_rotate(inputAngle);
			angle = inputAngle;
		}
		displayPosition(angle);
		displayPrompt("input: ");
	}

	return 0;
}
