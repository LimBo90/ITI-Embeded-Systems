/*
 * main.c
 *
 *  Created on: May 5, 2019
 *      Author: Administrator
 */

#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"
#include "MTIMER0_interface.h"
#include "avr/delay.h"

void initDCMotor(){
	MDIO_setPinDirection(PORTA, PIN_0, OUTPUT);
	MDIO_setPinDirection(PORTA, PIN_1, OUTPUT);

	MDIO_setPinDirection(PORTB, PIN_3, OUTPUT);	//set OC0 to be output
	MTIMER0_init(MTIMER0_MODE_PHASE_CORRECT_PWM, MTIMER0_PRESCALER_OFF);
	MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, 0);
	MTIMER0_startTimer();
}

void initStepperMotor(){
	MDIO_setPortDirection(PORTA, 0x0F, OUTPUT);
}
u8 stepMotorDirections[7] = {1,3,2,6,4,12,8};
int main(){
	//DC MOTOR
//	initDCMotor();
//	MDIO_setPinValue(PORTA, PIN_0, HIGH);
//	MDIO_setPinValue(PORTA, PIN_1, LOW);
//	MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, 250);
////	while(1){
////		for(u8 i = 0; i < 255; i++){
////			MTIMER0_PWM(MTIMER0_PWM_MODE_NON_INVERTED, i);
////			_delay_ms(10);
////		}
////	}
	initStepperMotor();
	while(1){
		for(u8 i = 0; i < 6 ; i++){
			MDIO_setPortToValue(PORTA, 0x0F, stepMotorDirections[i]);
			_delay_ms(2);
		}
//		for(u8 i = 0x08; i > 0; i>>=1){
//			MDIO_setPortToValue(PORTA, 0x0F, i);
//			_delay_ms(2);
//		}
	}

	return 0;
}

