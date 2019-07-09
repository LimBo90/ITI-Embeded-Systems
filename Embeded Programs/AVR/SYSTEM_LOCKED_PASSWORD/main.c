#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "LDelay.h"
//#include <util/delay.h>
#include "HKPD_interface.h"
#include "HLCD_interface.h"
#include "HLCD_interface.h"
#include "HEEPROM_interface.h"

#define PASS_MEM_LOCATION			50
#define TRIALS_COUNTER_MEM_LOCATION	60
#define PASSWORD_LENGTH 			4
#define MAX_ALLOWED_TRIALS 			3

typedef enum{
	ReceivingPass, SystemUnlocked, SystemLocked
}SystemState;

SystemState currentSystemState;
u8 pass[PASSWORD_LENGTH];
u8 remainingTrials;

void readRemainingTrialsCounterFromEEPROM(){
	u8 c;
	//read password trials counter
	HEEPROM_voidReadByte(TRIALS_COUNTER_MEM_LOCATION, &c);
	remainingTrials = c;
}

void displayPrompt(){
	HLCD_clearDisplay();
	HLCD_setCursor(1,0);
	HLCD_writeStr("Trials left: ");
	HLCD_writeNumber(remainingTrials);
	HLCD_setCursor(0,0);
	HLCD_writeStr("Password: ");

}

/**
 * Gets password from user
 */
void getPassword(){
	u8 c, i = 0;
	while(i < PASSWORD_LENGTH){
		while(!HKPD_getKey(&c));

		if( c == 'K'){
			if(i == 0)
				continue;
			//remove last character
			i--;
			HLCD_shiftCursorLeft(1);
			HLCD_writeData(' ');
			HLCD_shiftCursorLeft(1);
		}else{
			HLCD_writeData('*');
			pass[i] = c;
			i++;
		}
	}
}
/**
 * Checks if the password the user entered matches the password stored in EEPROM
 * Returns 0 if the password doesn't match
 * Returns 1 if the password matches
 */
u8 checkPassMatch(){
	u8 i, c, res = 1;
	for(i = 0; i < PASSWORD_LENGTH; i++){
		HEEPROM_voidReadByte(PASS_MEM_LOCATION + i, &c);
		if(c != pass[i]){
			res = 0;
			break;
		}
	}
	return res;
}

void unlockSystem(){
	HLCD_clearDisplay();
	HLCD_writeStr("System Unlocked");
}

void lockSystem(){
	HLCD_clearDisplay();
	HLCD_writeStr("System Locked");
}


int main(){
	HKPD_init();
	HLCD_init();
	HEEPROM_voidInit();
	readRemainingTrialsCounterFromEEPROM();
	displayPrompt();

	if(remainingTrials == 0)
		currentSystemState = SystemLocked;
	else
		currentSystemState = ReceivingPass;


	if(currentSystemState == ReceivingPass){
		//get password from user
		for(; remainingTrials > 0; remainingTrials--){
			displayPrompt();
			getPassword();
			if(checkPassMatch()){
				//if password correct unlock system
				HEEPROM_voidWriteByte(TRIALS_COUNTER_MEM_LOCATION, MAX_ALLOWED_TRIALS);
				LDelay_ms(2);
				currentSystemState = SystemUnlocked;
				break;
			}
			else{
				//decrement counter of remaining trials in EEPROM
				HEEPROM_voidWriteByte(TRIALS_COUNTER_MEM_LOCATION, remainingTrials-1);
				HLCD_clearDisplay();
				HLCD_writeStr("Wrong password");
				LDelay_ms(1000);
				currentSystemState = SystemLocked;
			}
		}
	}

	if(currentSystemState == SystemUnlocked)
		unlockSystem();
	else if(currentSystemState == SystemLocked)
		lockSystem();
	while(1);

}
