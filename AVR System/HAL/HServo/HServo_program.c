#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MTIMER0_private.h"
#include "MTIMER0_interface.h"
#include "HServo_interface.h"
#include "HLCD_interface.h"


void HServo_init(void){
    MTIMER1_init(MTIMER_MODE_14, MTIMER_PRESCALER_8);
    MTIMER1_setTOP(20000);
    MTIMER1_PWM(MTIMER0_PWM_MODE_NON_INVERTED, 1000);
    MTIMER1_startTimer();
}

void HServo_rotate(u8 angle){
    u16 value = (angle*10) + 500;
    MTIMER1_PWM(MTIMER0_PWM_MODE_NON_INVERTED, value);
}
