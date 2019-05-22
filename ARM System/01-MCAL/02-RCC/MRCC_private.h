#ifndef _MRCC_PRIVATE_H
#define _MRCC_PRIVATE_H

typedef struct{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCC;

#define MRCC ((volatile RCC *) (0x40021000))

#define MRCC_U8_REG_SIZE 32
#define MRCC_U8_AHB 	0
#define MRCC_U8_APB1 	1
#define MRCC_U8_APB2 	2
#endif
