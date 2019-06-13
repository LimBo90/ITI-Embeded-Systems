#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER0_interface.h"
#include "HLCD_interface.h"

#define SECOND_MS 1000


volatile u8 g_secs = 0;
volatile u8 g_mins = 0;
volatile u8 g_hrs = 0;

void clockTick(){
	g_secs++;
	if(g_secs == 60){
		g_mins++;
		g_secs = 0;
	}
	if(g_mins == 60){
		g_mins++;
		g_mins = 0;
	}
	displayClk();

}

void displayNumber(u8 n){
	if(n < 10){
		HLCD_writeData('0');
		HLCD_writeNumber(n);
	}else{
		HLCD_writeNumber(n);
	}
}

void displayClk(){
	HLCD_clearDisplay();
	displayNumber(g_hrs);
	HLCD_writeData(':');
	displayNumber(g_mins);
	HLCD_writeData(':');
	displayNumber(g_secs);
}

void mydelay(unsigned long time)
{
	u16 i;
	for(;time > 0; time--){
		for(i = 4000; i > 0; i--){
			asm("nop");
		}
	}
}


int main(){
	MTIMER_voidInit(SECOND_MS);
	MTIMER_registerISR(clockTick);
	HLCD_init();
	MDIO_setPinDirection(PORTA, PIN_0, OUTPUT);
	MDIO_setPinValue(PORTA, PIN_0, HIGH);
	while(1){
		mydelay(100);
		MDIO_togglePin(PORTA, PIN_0);
	}
	return 0;
}


