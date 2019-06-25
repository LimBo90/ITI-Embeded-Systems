#ifndef MTIMER_CONFIG_H_
#define MTIMER_CONFIG_H_

#define F_OSC 8000000

/************************* Timer0 ************************/
#define MTIMER0_CFG_PRESCALER				MTIMER_PRESCALER_8
#define MTIMER0_CFG_MODE					MTIMER_MODE_NORMAL
#define MTIMER0_CFG_INITIAL_STATE			MTIMER_INITIAL_STATE_DISABLED

/************************* Timer1 ************************/
#define MTIMER1_CFG_PRESCALER				MTIMER_PRESCALER_8
#define MTIMER1_CFG_MODE					MTIMER_MODE_NORMAL
#define MTIMER1_CFG_INITIAL_STATE			MTIMER_INITIAL_STATE_ENABLED

#endif
