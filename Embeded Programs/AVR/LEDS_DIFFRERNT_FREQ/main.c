#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER0_private.h"
#include "MTIMER0_interface.h"


void __vector_11 (void) __attribute__ ((signal, INTR_ATTRBS));
#define F_CPU 8000000
#define PRESCALER 8

#define DELAY_MS 1000


void toggleLEDS(){
	static u8 counter_500 = 0;
	static u8 counter_1000 = 0;

	counter_500++;
	counter_1000++;
	MDIO_togglePin(PORTA, PIN_0);
	if(counter_500 == 5){
		MDIO_togglePin(PORTA, PIN_1);
		counter_500 = 0;
	}

	if(counter_1000 == 10){
		MDIO_togglePin(PORTA, PIN_2);
		counter_1000 = 0;
	}
}

int main(){
	MTIMER_voidInit(100);
	MTIMER_registerISR(toggleLEDS);
	MDIO_setPinDirection(PORTA, PIN_0, OUTPUT);
	MDIO_setPinDirection(PORTA, PIN_1, OUTPUT);
	MDIO_setPinDirection(PORTA, PIN_2, OUTPUT);
	MDIO_setPinValue(PORTA, PIN_0, HIGH);
	MDIO_setPinValue(PORTA, PIN_1, HIGH);
	MDIO_setPinValue(PORTA, PIN_2, HIGH);
	while(1);
	return 0;
}
