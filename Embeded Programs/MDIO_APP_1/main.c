/*
 * main.c
 *
 *  Created on: Apr 15, 2019
 *      Author: Administrator
 */

#include <util/delay.h>
#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "HLED_interface.h"
#include "HSevenSegment_interface.h"

#define RIGHT 0
#define LEFT 1
#define PASS 0b00001001

#define ONES_SEVEN_SEGMENT PORTD
#define DIP_SWITCH PORTB
#define LEDS PORTA

void init(){
	HLED_initLEDS(LEDS, 0xFF);
	HSevenSegment_init(ONES_SEVEN_SEGMENT);
	MDIO_setPortDirection(DIP_SWITCH, 0x0F, INPUT_PULLUP);
}

int main(void){
	init();
	u8 n = 0, count=0, direction = LEFT;
	HSevenSegment_displayNum(ONES_SEVEN_SEGMENT, count);

	while(1){
		HLED_off(LEDS, n);
		HLED_off(LEDS, 7-n);
		n = (direction == LEFT)? n + 1 : n - 1;
		u8 value = (~MDIO_getPortValue(DIP_SWITCH, 0x0F)) & 0x0F;
		if(value == PASS){	//password checking
			n = (direction == LEFT)? n + 1 : n - 1;
		}else{
			n = 0;
			count = 0;
			HSevenSegment_displayNum(ONES_SEVEN_SEGMENT, count);
		}
		HLED_on(LEDS, n);
		HLED_on(LEDS, 7-n);
		if(n == 3){
			direction = RIGHT;
			count++;
			if(count == 10)
				count = 0;
			HSevenSegment_displayNum(ONES_SEVEN_SEGMENT, count);
		}else if(n == 0){
			direction = LEFT;
		}
		_delay_ms(500);
	}
	return 0;
}
