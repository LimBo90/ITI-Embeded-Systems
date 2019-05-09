///*
// * main.c
// *
// *  Created on: May 5, 2019
// *      Author: Administrator
// */
//
//#include "LUTILS.h"
//#include "LSTD_TYPES.h"
//#include "MDIO_interface.h"
//#include "MTIMER0_interface.h"
//#include <avr/delay.h>
//
//void toggleLED();
//
//void init(){
//	MDIO_setPinDirection(PORTA, PIN_0, OUTPUT);
//
//	//normal mode init
////	MTIMER0_init(MTIMER_MODE_NORMAL, MTIMER_PRESCALER_8);
////	MTIMER_enableGlobalInterrupts();
////	MTIMER0_enableNormalModeInterrupt();
////	MTIMER0_setDelay(1000);
//
//	//CTC mode init
////	MDIO_setPinDirection(PORTB, PIN_3, OUTPUT);	//set OC0 to be output
////	MTIMER0_init(MTIMER_MODE_CTC, MTIMER_PRESCALER_1024);
////	MTIMER_enableGlobalInterrupts();
////	MTIMER0_enableCTCModeInterrupt();
////	MTIMER0_setCompare(200,1000);
//
//	//fast PWM mode
//	MDIO_setPinDirection(PORTB, PIN_3, OUTPUT);	//set OC0 to be output
//	MTIMER0_init(MTIMER_MODE_PHASE_CORRECT_PWM, MTIMER_PRESCALER_OFF);
//	MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, 0);
//	MTIMER0_startTimer();
//
//
////	MTIMER0_registerISR(toggleLED);
////    MTIMER0_startTimer();
//}
//
//int main(){
//	init();
//	MDIO_setPinValue(PORTA, PIN_0, HIGH);
//	while(1){
//		// polling delay
////		MDIO_setPinValue(PORTA, PIN_0, HIGH);
////		MTIMER0_delay_ms(1000);
////		MDIO_setPinValue(PORTA, PIN_0, LOW);
////		MTIMER0_delay_ms(1000);
//		u8 i = 0;
//		for(i = 0; i < 254; i++){
//			MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, i);
//			_delay_ms(10);
//		}
//		for(i = 255; i > 0; i--){
//			MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, i);
//			_delay_ms(10);
//		}
//	}
//	return 0;
//}
//
//
//void toggleLED(){
//	MDIO_togglePin(PORTA, PIN_0);
//	MTIMER0_startTimer();
//}
