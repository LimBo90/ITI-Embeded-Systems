#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_


#include "LSTD_TYPES.h"

/**************** PORTS ********************/
#define MEXTI_MCUCR (*(volatile u8 *) (0x55))
#define MEXTI_MCUCSR (*(volatile u8 *) (0x54))
#define MEXTI_GICR (*(volatile u8 *) (0x5B))
#define MEXTI_GIFR (*(volatile u8 *) (0x5A))
#define MEXTI_SREG (*(volatile u8 *) (0x5F))

/***************** PINS ******************/
#define MEXTI_ISC00 0
#define MEXTI_ISC01 1
#define MEXTI_ISC10 2
#define MEXTI_ISC11 3

#define MEXTI_ISC2 6

#define MEXTI_INTF0 6
#define MEXTI_INTF1 7
#define MEXTI_INTF2 5

#define MEXTI_I 7





#endif
