/*
 * main.c
 *
 *  Created on: May 13, 2019
 *      Author: Administrator
 */

#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MEXTI_interface.h"
#include "MDIO_interface.h"
#include "MTIMER0_interface.h"
#include "HSevenSegment_interface.h"
#include "HServo_interface.h"
#include "HLCD_interface.h"

#define HSEVEN_PORT PORTB
#define SENSOR_PORT PORTD
#define SENSOR_ENTER_PIN PIN_2
#define SENSOR_EXIT_PIN PIN_3

u8 peopleCount = 0;

void openDoor(){
	HServo_rotate(180);
	MTIMER0_setDelay(2000);
	MTIMER0_startTimer();
}

void closeDoor(){
	HServo_rotate(0);
	MTIMER0_stopTimer();
}

void enterPeople(){
	if(peopleCount < 3){
		openDoor();
		peopleCount++;
	}

	if(peopleCount == 3)
		MDIO_setPinValue(PORTD, PIN_0, HIGH);

}

void exitPeople(){
	if(peopleCount > 0){
		openDoor();
		peopleCount--;
	}
	if(peopleCount < 3)
		MDIO_setPinValue(PORTD, PIN_0, LOW);
}

void init(){
	HSevenSegment_init(HSEVEN_PORT);

	//buzzer
	MDIO_setPinDirection(PORTD, PIN_0, OUTPUT);

	MDIO_setPinDirection(PORTD, PIN_2, INPUT_PULLUP);
	MDIO_setPinDirection(PORTD, PIN_3, INPUT_PULLUP);
	MEXTI_enableInterrupts();
	MEXTI_enableINT(MEXTI_INT0, MEXTI_MODE_FALLING_EDGE);
	MEXTI_enableINT(MEXTI_INT1, MEXTI_MODE_FALLING_EDGE);
	MEXTI_registerISR(MEXTI_INT0, enterPeople);
	MEXTI_registerISR(MEXTI_INT1, exitPeople);

	MTIMER0_init(MTIMER_MODE_NORMAL, MTIMER_PRESCALER_8);
	MTIMER0_enableNormalModeInterrupt();
	MTIMER0_registerISR(closeDoor);

	HLCD_init();
	HLCD_clearDisplay();

	MDIO_setPinDirection(PORTD, PIN_5, OUTPUT);
	HServo_init();
}

int main(){
	init();
	while(1){
		HSevenSegment_displayNum(PORTB, peopleCount);
	}
	return 0;
}
