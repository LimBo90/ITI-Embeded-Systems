/*
 * main.c
 *
 *  Created on: May 8, 2019
 *      Author: Administrator
 */


#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "HLCD_interface.h"
#include "MTIMER0_interface.h"
#define F_CPU 8000000


void init(){
	HLCD_init();

	MTIMER0_init(MTIMER_MODE_FAST_PWM, MTIMER_PRESCALER_8);

	//fast PWM mode
	MDIO_setPinDirection(PORTB, PIN_3, OUTPUT);	//set OC0 to be output
	MTIMER0_init(MTIMER_MODE_PHASE_CORRECT_PWM, MTIMER_PRESCALER_8);
	MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, 2);
	MTIMER0_startTimer();

	//timer 1
	MDIO_setPinDirection(PORTD, PIN_6, INPUT);
	MTIMER1_init(MTIMER_MODE_NORMAL, MTIMER_PRESCALER_8);
	MTIMER_enableGlobalInterrupts();
	MTIMER1_enableInputCaptureInterrupt();
	MTIMER1_startTimer();

}
int main(){
	init();
	u8 buffer[20];

	while(1){
		HLCD_setCursor(0,0);
		HLCD_writeStr("Period = ");
		itoa(MTIMER1_getPeriod(), buffer, 10);
		HLCD_writeStr(buffer);
//		HLC_setCursor(1, 5);
//		itoa(MTIMER1_getDutyCycle(), buffer, 10);
//		HLCD_writeStr(buffer);
	}


	return 0;
}
