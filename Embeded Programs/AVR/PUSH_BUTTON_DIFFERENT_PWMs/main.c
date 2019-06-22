#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER_interface.h"
#include "HPB_interface.h"

#define SWITCH_20 0
#define SWITCH_40 1
#define SWITCH_60 2
#define SWITCH_90 3


int main(){
	//peripherals used for debugging  initialization
	MUART_voidInit();


	//This pin is used as Vcc for the pull down switches
	MDIO_setPinDirection(PORTC, PIN_7, OUTPUT);
	MDIO_setPinValue(PORTC, PIN_7, HIGH);

	//timer 1 initalization for PWM
	MDIO_setPinDirection(PORTD, PIN_5, OUTPUT);
	MTIMER_voidInit(MTIMER_TIMER1);
	MTIMER_voidSetPwmWithFreq(20, 0);
	MTIMER_voidStartTimer(MTIMER_TIMER1);

	//push button initalization
	HPB_init();

	while(1){
		if(HPB_getState(SWITCH_20) == HPB_Pressed)
			MTIMER_voidSetPwmWithFreq(20, 20);
		else if(HPB_getState(SWITCH_40) == HPB_Pressed)
			MTIMER_voidSetPwmWithFreq(20, 40);
		else if(HPB_getState(SWITCH_60) == HPB_Pressed)
			MTIMER_voidSetPwmWithFreq(20, 60);
		else if(HPB_getState(SWITCH_90) == HPB_Pressed)
			MTIMER_voidSetPwmWithFreq(20, 90);
		else
			MTIMER_voidSetPwmWithFreq(20, 0);
	}

	return 0;
}
