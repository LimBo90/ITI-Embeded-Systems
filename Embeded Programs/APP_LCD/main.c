/*
 * main.c
 *
 *  Created on: Apr 16, 2019
 *      Author: Administrator
 */
#include "util/delay.h"
#include "HLCD_interface.h"
#define F_CPU 8000000

int main(){
	u8 customCharacter[7] = {0xFF, 0b00010011, 0b00010111,0b00011101,0b00011001,0b00011001,0xFF};
	HLCD_init();
	HLCD_clearDisplay();
	HLCD_addCustomCharacter(1,customCharacter);
	HLCD_displayCustomCharacter(1);

	return 0;
}
