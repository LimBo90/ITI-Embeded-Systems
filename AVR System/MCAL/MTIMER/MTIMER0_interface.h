#ifndef MTIMER0_INTERFACE_H_
#define MTIMER0_INTERFACE_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include "MTIMER0_private.h"
#include "LSTD_TYPES.h"

/*********** VALUES *********/
//prescaler
#define MTIMER0_PRESCALER_OFF 1
#define MTIMER0_PRESCALER_8 2
#define MTIMER0_PRESCALER_64 3
#define MTIMER0_PRESCALER_256 4
#define MTIMER0_PRESCALER_1024 5
#define MTIMER0_EXTERNAL_FALLING_EDGE 6
#define MTIMER0_EXTERNAL_RISING_EDGE 7

//modes
#define MTIMER0_MODE_NORMAL 0
#define MTIMER0_MODE_PWM 1
#define MTIMER0_MODE_CTC 2
#define MTIMER0_MODE_FAST_PWM 3

void MTIMER0_init(u8 mode, u8 prescaler);
void MTIMER0_delay_ms(u32 delay);
void MTIMER0_enableInterrupt();
void MTIMER0_disableInterrupt();
void MTIMER0_registerISR(void (*isr_func)(void));
void MTIMER0_setDelay(u32 delay);
void MTIMER0_stopTimer();
void MTIMER0_startTimer();
#endif
