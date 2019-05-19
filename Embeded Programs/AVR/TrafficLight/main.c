/*
 * main.c
 *
 *  Created on: Apr 21, 2019
 *      Author: Administrator
 */
#include "MDIO_interface.h"
#include "HLED_interface.h"
#include "HLCD_interface.h"
#include "HSevenSegment_interface.h"
#include "util/delay.h"

#define SEVEN_SEGMENT_PORT PORTA
#define LEDS_PORT PORTB
#define RED_LED PIN_0
#define YELLOW_LED PIN_1
#define GREEN_LED PIN_2
#define BUZZER_PIN PIN_3



void init(){
	u8 heart[7] = {0b00010010,0b00011011, 0b00011111, 0b00011111, 0b00001110, 0b00001110, 0b0000100};
	HLCD_addCustomCharacter(0, heart);
	HLED_init(LEDS_PORT, RED_LED);
	HLED_init(LEDS_PORT, YELLOW_LED);
	HLED_init(LEDS_PORT, GREEN_LED);
	HLED_init(LEDS_PORT, BUZZER_PIN);
	HSevenSegment_init(SEVEN_SEGMENT_PORT);	//test seven segment
	HLCD_init();
	HLCD_writeStr("   I ");
	HLCD_displayCustomCharacter(0);
	HLCD_writeStr(" ITI");
	HLCD_setCursor(0, 16);
	HLCD_writeStr("Project by: ");
	HLCD_setCursor(1, 20);
	HLCD_writeStr("Abdullah");
}

void main(){
	init();

	while(1){
		for(u8 i = 0; i < 2 ; i++){
			HLED_on(LEDS_PORT, i? GREEN_LED : RED_LED);
			HLED_off(LEDS_PORT, i? RED_LED : GREEN_LED);
			for(int timer = 9; timer >= 0 ; timer--){
				HSevenSegment_displayNum(SEVEN_SEGMENT_PORT, timer);
				if(timer <= 5){
					HLED_on(LEDS_PORT, BUZZER_PIN);
					HLED_on(LEDS_PORT, YELLOW_LED);
					_delay_ms(500);
					HLED_off(LEDS_PORT, BUZZER_PIN);
					HLED_off(LEDS_PORT, YELLOW_LED);
					_delay_ms(500);
				}else{
					_delay_ms(1000);
				}
			}
			HLCD_shiftDisplay(i? HLCD_RIGHT :  HLCD_LEFT, 25);
		}
	}
}



