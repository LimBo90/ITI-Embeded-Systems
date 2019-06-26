/*
 * HICU_private.h
 *
 *  Created on: Jun 25, 2019
 *      Author: Abdelrahman
 */

#ifndef HICU_PRIVATE_H_
#define HICU_PRIVATE_H_

/**
 * Which external interrupt is used either INT0, INT1 or INT2
 */
#if HICU_CFG_EXTI == HICU_EXTI0
#define HICU_EXTI	MEXTI_INT0
#elif HICU_CFG_EXTI == HICU_EXTI1
#define HICU_EXTI MEXTI_INT1
#elif HICU_CFG_EXTI == HICU_EXTI2
#define HICU_EXTI MEXTI_INT2
#else
#error "HICU_CFG_EXTI not configure correctly in HICU_config.h. HICU_CFG_EXTI can only be either HICU_EXTI0, HICU_EXTI1 or HICU_EXTI2"
#endif


#if HICU_CFG_TIMER == HICU_TIMER0
	#define HICU_TIMER	MTIMER_TIMER0
	#define HICU_TIMER_MAX_COUNT	MTIMER0_MAX_COUNT
#elif HICU_CFG_TIMER == HICU_TIMER1
	#define HICU_TIMER MTIMER_TIMER1
	#define HICU_TIMER_MAX_COUNT	MTIMER1_MAX_COUNT
#else
	#error "HICU_CFG_TIMER configured incorrectly in HICU_config.h"
#endif

void HICU_voidMeasurePWM();
void HICU_voidCountOverflows();

#endif /* HICU_PRIVATE_H_ */
