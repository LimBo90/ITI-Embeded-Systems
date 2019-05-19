#ifndef _MRCC_PRIVATE_H
#define _MRCC_PRIVATE_H

#define MRCC_CR 		*((u32*) 0x40021000)
#define MRCC_CFGR 		*((u32*) 0x40021004)
#define MRCC_CIR 		*((u32*) 0x40021008)
#define MRCC_APB2RSTR 	*((u32*) 0x4002100C)
#define MRCC_APB1RSTR 	*((u32*) 0x40021010)
#define MRCC_AHBENR 	*((u32*) 0x40021014)
#define MRCC_APB2ENR 	*((u32*) 0x40021018)
#define MRCC_APB1ENR 	*((u32*) 0x4002101C)
#define MRCC_BDCR	 	*((u32*) 0x40021020)
#define MRCC_CSR	 	*((u32*) 0x40021024)



#define MRCC_U8_REG_SIZE 32
#define MRCC_U8_AHB 	0
#define MRCC_U8_APB1 	1
#define MRCC_U8_APB2 	2
#endif