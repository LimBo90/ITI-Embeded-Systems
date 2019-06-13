#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER0_interface.h"
#include "HLCD_interface.h"


#define SYSTOL_DURATION_MS	 400
#define DIASTOLE_DURATION_MS 600
#define GRETEAST_COMMON_DIVISOR 200

#define SMALL_HEART 0
#define BIG_HEART 1

void heartPulse();

void init(){
	u8 BIG_HEART_PATTERN[7] = { 0x00, 0x0E, 0x1F, 0x1F, 0x0E, 0x04, 0x00};
//	u8 SMALL_HEART_PATTERN[7] = { 0x00, 0x0E, 0x11, 0x11, 0x0A, 0x04, 0x00};
	u8 SMALL_HEART_PATTERN[7] = { 0x00, 0x00, 0x0E, 0x0E, 0x04, 0x00, 0x00};

	MTIMER_voidInit(GRETEAST_COMMON_DIVISOR);
	MTIMER_registerISR(heartPulse);
	HLCD_init();
	HLCD_addCustomCharacter(BIG_HEART, BIG_HEART_PATTERN);
	HLCD_addCustomCharacter(SMALL_HEART, SMALL_HEART_PATTERN);

}

void heartPulse(){
	static u8 counter = 0;
	counter++;

	if(counter == SYSTOL_DURATION_MS/GRETEAST_COMMON_DIVISOR){
		HLCD_setCursor(0, 0);
		HLCD_displayCustomCharacter(BIG_HEART);
	}
	if(counter ==  (SYSTOL_DURATION_MS + DIASTOLE_DURATION_MS) /GRETEAST_COMMON_DIVISOR){
		HLCD_setCursor(0, 0);
		HLCD_displayCustomCharacter(SMALL_HEART);
		counter = 0;
	}

}

int main(){
	init();
	HLCD_setCursor(1,1);
	HLCD_displayCustomCharacter(BIG_HEART);
	HLCD_displayCustomCharacter(SMALL_HEART);
	HLCD_setCursor(0, 0);
	while(1);
	return 0;
}

