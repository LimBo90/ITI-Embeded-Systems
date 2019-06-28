/*
 * HICU_config.h
 *
 *  Created on: Jun 25, 2019
 *      Author: Abdelrahman
 */

#ifndef HICU_CONFIG_H_
#define HICU_CONFIG_H_





/**
 * Chooses which external interrupt to use
 */

#define HICU_EXTI0  0
#define HICU_EXTI1  1
#define HICU_EXTI2  2

#define HICU_CFG_EXTI HICU_EXTI0

/**
 * Chooses which timer is used
 */
#define HICU_TIMER0	0
#define HICU_TIMER1	1

#define HICU_CFG_TIMER HICU_TIMER1

#endif /* HICU_CONFIG_H_ */
