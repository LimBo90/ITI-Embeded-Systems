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
#define MTIMER_MODE_PHASE_CORRECT_PWM 	0b00000001
#define MTIMER_MODE_CTC					0b00001000
#define MTIMER_MODE_FAST_PWM 			0b00001001

//initial state
#define MTIMER_INITIAL_STATE_ENABLED	0
#define MTIMER_INITIAL_STATE_DISABLED	1

//pwm_modes
#define MTIMER0_PWM_MODE_INVERTED 		0
#define MTIMER0_PWM_MODE_NON_INVERTED	1

//Timer Selection
#define MTIMER_TIMER0 0
#define MTIMER_TIMER1 1

/**
 * Initalizes timer
 */
void MTIMER_voidInit(u8 Copy_u8Timer);

/**
 * Sets the time after which the the timer will call the overflow callback function
 * callback function is specified using MTIMER_voidSetOVCallback()
 */
void MTIMER_voidSetDesiredTime(u8 Copy_u8Timer, u32 Copy_u32Time_ms);

/**
 * Sets the time after which the timer will call the compare match callback function
 * callback function is specified using MTIMER_voidSetCompareMatchCallback().
 * The OCR provided is the value that will be put in OCR register to compare the counter with.
 * Input:
 * 			Copy_u8Timer 				The timer whose CTC mode will be configured (either MTIMER_TIMER0 or MTIMER_TIMER1)
 * 			OCR					The value that will be put in OCR register. Take care that when working with timer0 OCR has to be 1 byte only
 * 			Copy_u32Time_ms		The time after which the the timer will call the overflow callback function
 * 								callback function is specified using MTIMER_voidSetCompareMatchCallback()
 */
void MTIMER_voidSetCTC(u8 Copy_u8Timer, u16 OCR, u32 Copy_u32Time_ms);
void MTIMER_voidSetCTC_us(u8 Copy_u8Timer, u16 Copy_u16OCR, u32 Copy_u32Time_us);
/**
 * Sets callBack function that's called when the timer reaches the time speciied in setDesiredTime()
 */
void MTIMER_voidSetOVCallback(u8 Copy_u8Timer, void (*func)(void));

void MTIMER_voidSetCompareMatchCallback(u8 Copy_u8Timer, void (*func)(void));

/**
 * Starts timer
 */
void MTIMER_voidStartTimer(u8 Copy_u8Timer);

/**
 * Stops the timer
 */
void MTIMER_voidStopTimer(u8 Copy_u8Timer);

/**
 * Disable and enable interrupts
 */
void MTIMER_voidEnableOverflowInterrupt(u8 Copy_u8Timer);
void MTIMER_voidDisableOverflowInterrupt(u8 Copy_u8Timer);
void MTIMER_voidEnableCompareMatchInterrupt(u8 Copy_u8Timer);
void MTIMER_voidDisableCompareMatchInterrupt(u8 Copy_u8Timer);
void MTIMER_voidEnableGlobalInterrupts(void);
void MTIMER_voidDisableGlobalInterrupts(void);
void displayNumbers(u8 timer);
#endif
