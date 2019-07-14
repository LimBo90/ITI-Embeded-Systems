#ifndef _MSTK_CONFIG_H_
#define _MSTK_CONFIG_H_


/**
 * This is the clock for the systick
 */
#define MSTK_CLK_AHB	1
#define	MSTK_CLK_AHB_8	0
#define MSTK_CLK	MSTK_CLK_AHB_8

/**
 * Interrupt status of the systick
 */
#define MSTK_INTERRUPT_ENABLED
#define MSTK_INTERRUPT_DISABLED
#define MSTK_INTERRUPT_STATUS	MSTK_INTERRUPT_ENABLED


#endif
