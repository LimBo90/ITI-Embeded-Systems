/*
 * main.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Administrator
 */

#include <avr/io.h>


int main(void){
	DDRA = 0b00000001;
	PORTA = 0b00000001;

	return 0;
}

