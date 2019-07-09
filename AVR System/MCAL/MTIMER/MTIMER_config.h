#ifndef MTIMER_CONFIG_H_
#define MTIMER_CONFIG_H_

/***********************************************************************/
/*********** Configurations Values (never change these values) *********/
/***********************************************************************/

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
#define MTIMER_MODE_FAST_PWM_14 		0b00011010

//initial state
#define MTIMER_INITIAL_STATE_ENABLED	0
#define MTIMER_INITIAL_STATE_DISABLED	1

/**************************************************************************/
/*********************** Configurations ************************************/
/*************************************************************************/


#define F_OSC 8000000		// system frequency
/************************* Timer0 ************************/
#define MTIMER0_CFG_PRESCALER				MTIMER_PRESCALER_8
#define MTIMER0_CFG_MODE					MTIMER_MODE_CTC
#define MTIMER0_CFG_INITIAL_STATE			MTIMER_INITIAL_STATE_DISABLED

/************************* Timer1 ************************/
#define MTIMER1_CFG_PRESCALER				MTIMER_PRESCALER_8
#define MTIMER1_CFG_MODE					MTIMER_MODE_NORMAL
#define MTIMER1_CFG_INITIAL_STATE			MTIMER_INITIAL_STATE_DISABLED

#endif
