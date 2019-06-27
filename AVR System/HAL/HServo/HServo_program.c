#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MDIO_interface.h"
#include "MTIMER_interface.h"
#include "MUART_interface.h"
#include "HServo_interface.h"

void HServo_init(void){
	MDIO_setPinDirection(PORTD, PIN_5, OUTPUT);
	MTIMER_voidInit(MTIMER_TIMER1);
	MTIMER_voidSetPwmWithFreq(20,0);
    MTIMER_voidStartTimer(MTIMER_TIMER1);

}

void HServo_rotate(u8 angle){
    u16 value = (50 + angle) / 2;
	MTIMER_voidSetPwmWithFreq(20,value);
}
