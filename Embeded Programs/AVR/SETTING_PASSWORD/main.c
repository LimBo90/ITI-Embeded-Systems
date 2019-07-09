/*
 * main.c
 *
 *  Created on: Jun 28, 2019
 *      Author: Abdelrahman
 */
#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "LDelay.h"

#include "MUART_interface.h"
#include "HEEPROM_interface.h"
#include "HLCD_interface.h"

#define PASS_MEM_LOCATION			50
#define TRIALS_COUNTER_MEM_LOCATION	60
#define PASSWORD_LENGTH 			4
#define MAX_ALLOWED_TRIALS 			3

typedef enum {
	ReceivingPass, PasswordReceived, PasswordSaved
}SystemState;

u8 pass[PASSWORD_LENGTH];
SystemState currentState;

void recievePassHandler(u8 c);
void confirmingPassHandler(u8 c);

/**
 * Handler for receiving password
 */
void recievePassHandler(u8 c){
	static u8 counter = 0;
	pass[counter] = c;
	counter++;
	if(counter == PASSWORD_LENGTH){
		MUART_u8SendStr("\nConfirm your Password\n");
		MUART_voidSetOnRecieveCallback(confirmingPassHandler);
		counter = 0;
	}
}

/**
 * Handler for confirming recieved password
 */
void confirmingPassHandler(u8 c){
	static u8 counter = 0;
	static u8 pass2[PASSWORD_LENGTH];
	pass2[counter] = c;
	counter++;

	if(counter == PASSWORD_LENGTH){
		u8 passwordsMatch = 1;
		for(counter = 0; counter < PASSWORD_LENGTH; counter++){
			if(pass[counter] != pass2[counter]){
				passwordsMatch = 0;
				MUART_u8SendStr("\nWrong password. Re-enter password\n");
				MUART_voidSetOnRecieveCallback(recievePassHandler);
				break;
			}
		}
		if(passwordsMatch){
			currentState = PasswordReceived;
		}
		counter = 0;
	}
}

/**
 * Saves password in EEPROM and reset number of allowed password trials
 */
void savePassword(){
	u8 i;
	for(i = 0; i < PASSWORD_LENGTH; i++){
		HEEPROM_voidWriteByte(PASS_MEM_LOCATION + i, pass[i]);
		LDelay_ms(2);
	}
	//reset password trials counter
	HEEPROM_voidWriteByte(TRIALS_COUNTER_MEM_LOCATION, MAX_ALLOWED_TRIALS);
}

int main(){
	MUART_voidInit();
	HLCD_init();
	HEEPROM_voidInit();
	currentState = ReceivingPass;
	MUART_voidSetOnRecieveCallback(recievePassHandler);
	MUART_u8SendStr("\nEnter your password\n");

	while(1){
		if(currentState == PasswordReceived){
			savePassword();
			MUART_u8SendStr("\nPassword Saved!");
			currentState = PasswordSaved;
			u8 c;
			MUART_u8SendStr("\nPass = ");
			for(u8 i = 0; i < PASSWORD_LENGTH; i++){
				HEEPROM_voidReadByte(
						PASS_MEM_LOCATION + i, &c);
				MUART_u8SendByte(c);
			}
			HEEPROM_voidReadByte(TRIALS_COUNTER_MEM_LOCATION , &c);
			MUART_u8SendStr("\nallowedTrials = ");
			MUART_u8SendByte(c);
		}
	}
}
