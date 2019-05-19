#ifndef _MRCC_INTERFACE_H_
#define _MRCC_INTERFACE_H_

#define MRCC_U8_DMA1	0
#define MRCC_U8_DMA2	1
#define MRCC_U8_SRAM	2
#define MRCC_U8_FLITF	4
#define MRCC_U8_CRCE	6
#define MRCC_U8_FSMC	8
#define MRCC_U8_SDIO	10
#define MRCC_U8_TIM2	32
#define MRCC_U8_TIM3	33

#define MRCC_U8_AFIO	64
#define MRCC_U8_GPIOA	66
#define MRCC_U8_GPIOB	67
#define MRCC_U8_GPIOC	68


void MRCC_voidEnPeriphClk(u8 Copy_u8PeriphIdx);

#endif