#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

#ifndef F_CPU
	#define F_CPU 8000000
#endif

#include "MTIMER_private.h"
#include "LSTD_TYPES.h"

/*********** Configurations *********/
//prescaler
#define MTIMER_PRESCALER_OFF 			0b00000001
#define MTIMER_PRESCALER_8 				0b00000010
#define MTIMER_PRESCALER_64 			0b00000011
#define MTIMER_PRESCALER_256 			0b00000100
#define MTIMER_PRESCALER_1024 			0b00000101
#define MTIMER_EXTERNAL_FALLING_EDGE	0b00000110
#define MTIMER_EXTERNAL_RISING_EDGE 	0b00000111

//modes in timer 0 and timer 1
#define MTIMER_MODE_NORMAL				0b00000000
#define MTIMER_MODE_PHASE_CORRECT_PWM 	0b01000000
#define MTIMER_MODE_CTC					0b00001000
#define MTIMER_MODE_FAST_PWM 			0b01001000

//initial state
#define MTIMER_INITIAL_STATE_ENABLED	0
#define MTIMER_INITIAL_STATE_DISABLED	1


//pwm_modes
#define MTIMER0_PWM_MODE_INVERTED 		0
#define MTIMER0_PWM_MODE_NON_INVERTED	1


//different timers
#define MTIMER_TIMER0 0
#define MTIMER_TIMER1 1

/**
 * Initalizes timer
 */
void MTIMER_voidInit(void);

/**
 * Sets the time after which the the timer will call the callback function
 * callback function is specified using setCallBack()
 */
void MTIMER_voidSetDesiredTime(u32 Copy_u32Time_ms);

void MTIMER_voidSetCTC(u8 OCR, u32 Copy_u32Time_ms);

/**
 * Sets callBack function that's called when the timer reaches the time speciied in setDesiredTime()
 */
void MTIMER_voidSetOVCallback(void (*func)(void));

void MTIMER_voidSetCompareMatchCallback(void (*func)(void));

/**
 * Starts timer
 */
void MTIMER_voidStartTimer(void);

/**
 * Stops the timer
 */
void MTIMER_voidStopTimer(void);

/**
 * Disable and enable interrupts
 */
void MTIMER_voidEnableOverflowInterrupt(void);
void MTIMER_voidDisableOverflowInterrupt(void);
void MTIMER_voidEnableCompareMatchInterrupt(void);
void MTIMER_voidDisableCompareMatchInterrupt(void);
void MTIMER_voidEnableGlobalInterrupts(void);
void MTIMER_voidDisableGlobalInterrupts(void);
#endif
