/*
 * main.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Administrator
 */
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

const uint8_t SEVEN_SEGMENT_CODES[10] = {0b11000000, 0b11001111, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
typedef enum{
	UP,
	DOWN
}Direction;


void displayNum(uint8_t n){
	if(n > 9)
		return;
	PORTA = SEVEN_SEGMENT_CODES[n];
	return;
}

int main(void){

	DDRA = 0b11111111;
	DDRC = 0b11110000;
	PORTC = 0b11111111;



	while(1){
		uint8_t n = ~(PINC);
		displayNum(n);
	}

	return 0;
}

