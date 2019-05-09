#ifndef MTIMER0_INTERFACE_H_
#define MTIMER0_INTERFACE_H_

#ifndef F_CPU
	#define F_CPU 8000000
#endif

#include "MTIMER0_private.h"
#include "LSTD_TYPES.h"

/*********** VALUES *********/
//prescaler
#define MTIMER_PRESCALER_OFF 1
#define MTIMER_PRESCALER_8 2
#define MTIMER_PRESCALER_64 3
#define MTIMER_PRESCALER_256 4
#define MTIMER_PRESCALER_1024 5
#define MTIMER_EXTERNAL_FALLING_EDGE 6
#define MTIMER_EXTERNAL_RISING_EDGE 7

//modes
#define MTIMER_MODE_NORMAL 0
#define MTIMER_MODE_PHASE_CORRECT_PWM 1
#define MTIMER_MODE_CTC 2
#define MTIMER_MODE_FAST_PWM 3

//pwm_modes
#define MTIMER0_PWM_MODE_INVERTED 0
#define MTIMER0_PWM_MODE_NON_INVERTED 1

//TIMER0
void MTIMER0_init(u8 mode, u8 prescaler);
void MTIMER0_delay_ms(u32 delay);
void MTIMER_enableGlobalInterrupts();
void MTIMER0_enableNormalModeInterrupt();
void MTIMER0_disableNormalModeInterrupt();
void MTIMER0_enableCTCModeInterrupt();
void MTIMER0_disableCTCModeInterrupt();
void MTIMER0_registerISR(void (*isr_func)(void));
void MTIMER0_setCompare(u8 OCR, u32 delay);
void MTIMER0_setDelay(u32 delay);
void MTIMER0_PWM(u8 mode, u8 dutyCycle);
void MTIMER0_stopTimer();
void MTIMER0_startTimer();


//TIMER1
void MTIMER1_init(u8 mode, u8 prescaler);
void MTIMER1_enableInputCaptureInterrupt();
void MTIMER1_disableInputCaptureInterrupt();
u16 MTIMER1_getPeriod();
u16 MTIMER1_getDutyCycle();
void MTIMER1_startTimer();
void MTIMER1_stopTimer();
#endif
