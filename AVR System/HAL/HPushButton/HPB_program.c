#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER_interface.h"
#include "MUART_interface.h"

#include "HPB_interface.h"
#include "HPB_private.h"
#include "HPB_config.h"

u8 const PORTS[HPB_NO_OF_BUTTONS] = HPB_PORTS;
u8 const PINS[HPB_NO_OF_BUTTONS] = HPB_PINS;
u8 const CONNECTIONS[HPB_NO_OF_BUTTONS] = HPB_CONNECTIONS;

volatile HPB_State g_currentState[HPB_NO_OF_BUTTONS];
volatile u8 g_consecutiveHighs[HPB_NO_OF_BUTTONS] = {0};
volatile u8 g_consecutiveLows[HPB_NO_OF_BUTTONS] = {0};

/**
 * Initalizes push button
 */
void HPB_init(void){
	//Initalizes buttons pins
	u8 i;
	for(i = 0; i < HPB_NO_OF_BUTTONS; i++){
		if(CONNECTIONS[i] == HPB_CONNECTION_PULLUP)
			MDIO_setPinDirection(PORTS[i], PINS[i], INPUT_PULLUP);
		else if(CONNECTIONS[i] == HPB_CONNECTION_PULLDOWN)
			MDIO_setPinDirection(PORTS[i], PINS[i], INPUT);
	}

	//initalizes timer to call updateState every 5ms
	MTIMER_voidInit(MTIMER_TIMER0);	//initalizes timer
	MTIMER_voidEnableGlobalInterrupts();
	MTIMER_voidEnableCompareMatchInterrupt(MTIMER_TIMER0);
	MTIMER_voidSetCTC(MTIMER_TIMER0, 250, HPB_SAMPLE_TIME_MS);	//set compare match
	MTIMER_voidSetCompareMatchCallback(MTIMER_TIMER0, HPB_updateState);	//subscripe update state to timer
	displayNumbers(MTIMER_TIMER0);
	MTIMER_voidStartTimer(MTIMER_TIMER0);
}

/**
 * Returns the state of the push button
 */
HPB_State HPB_getState(u8 Copy_u8ButtonIndx){
	return g_currentState[Copy_u8ButtonIndx];
}

/**
 * Updates the state of the push button --> this function is subscriped to a timer and called periodically
 */
void HPB_updateState(void){
	u8 i;
	for(i = 0; i < HPB_NO_OF_BUTTONS; i++){
		//get switch sample
		u8 sample = MDIO_getPinValue(PORTS[i], PINS[i]);

		//update number of consecutive highs and lows
		if(sample == HIGH){
			g_consecutiveHighs[i]++;
			g_consecutiveLows[i] = 0;
		}else{
			g_consecutiveLows[i]++;
			g_consecutiveHighs[i] = 0;
		}

		//calculate the next state
		switch(g_currentState[i]){
		case HPB_Released:
			if(CONNECTIONS[i] == HPB_CONNECTION_PULLUP && sample == LOW)
				g_currentState[i] = HPB_Bouncing;
			else if(CONNECTIONS[i] == HPB_CONNECTION_PULLDOWN && sample == HIGH )
				g_currentState[i] = HPB_Bouncing;
			break;
		case HPB_Pressed:
			if(CONNECTIONS[i] == HPB_CONNECTION_PULLUP && sample == HIGH)
				g_currentState[i] = HPB_Bouncing;
			else if(CONNECTIONS[i] == HPB_CONNECTION_PULLDOWN && sample == LOW)
				g_currentState[i] = HPB_Bouncing;
			break;

		case HPB_Bouncing:
			switch(CONNECTIONS[i]){
				case HPB_CONNECTION_PULLUP:
					if(g_consecutiveHighs[i] >= HPB_NO_OF_SAMPLES_TO_CHANGE_STATE)
						g_currentState[i] = HPB_Released;
					else if(g_consecutiveLows[i] >= HPB_NO_OF_SAMPLES_TO_CHANGE_STATE)
						g_currentState[i] = HPB_Pressed;
					break;
				case HPB_CONNECTION_PULLDOWN:
					if(g_consecutiveHighs[i] >= HPB_NO_OF_SAMPLES_TO_CHANGE_STATE)
						g_currentState[i] = HPB_Pressed;
					else if(g_consecutiveLows[i] >= HPB_NO_OF_SAMPLES_TO_CHANGE_STATE)
						g_currentState[i] = HPB_Released;
					break;
			}
			break;
		}
	}
}
