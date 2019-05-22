#ifndef _MRCC_INTERFACE_H_
#define _MRCC_INTERFACE_H_

//AHB
#define MRCC_U8_DMA1	0
#define MRCC_U8_DMA2	1
#define MRCC_U8_SRAM	2
#define MRCC_U8_FLITF	4
#define MRCC_U8_CRCE	6
#define MRCC_U8_FSMC	8
#define MRCC_U8_SDIO	10

//APB1
#define MRCC_U8_TIM2	32
#define MRCC_U8_TIM3	33
#define MRCC_U8_TIM4	34
#define MRCC_U8_TIM5	35
#define MRCC_U8_TIM6	36
#define MRCC_U8_TIM7	37
#define MRCC_U8_TIM12	38
#define MRCC_U8_TIM13	39
#define MRCC_U8_TIM14	40
#define MRCC_U8_WWDG	43
#define MRCC_U8_SPI2	46
#define MRCC_U8_SPI3	47
#define MRCC_U8_USART2	49
#define MRCC_U8_USART3	50
#define MRCC_U8_UART4	51
#define MRCC_U8_UART5	52
#define MRCC_U8_I2C1	53
#define MRCC_U8_I2C2	54
#define MRCC_U8_USB 	55
#define MRCC_U8_CAN 	57
#define MRCC_U8_BKP 	59
#define MRCC_U8_PWR 	60
#define MRCC_U8_DAC 	61

//APB2
#define MRCC_U8_AFIO	64
#define MRCC_U8_GPIOA	66
#define MRCC_U8_GPIOB	67
#define MRCC_U8_GPIOC	68
#define MRCC_U8_GPIOD	69
#define MRCC_U8_GPIOE	70
#define MRCC_U8_GPIOF	71
#define MRCC_U8_GPIOG	72
#define MRCC_U8_ADC1	73
#define MRCC_U8_ADC2	74
#define MRCC_U8_TIM1	75
#define MRCC_U8_SPI1	76
#define MRCC_U8_TIM8	77
#define MRCC_U8_USART1	78
#define MRCC_U8_ADC3	79
#define MRCC_U8_TIM9	83
#define MRCC_U8_TIM10	84
#define MRCC_U8_TIM11	85

void MRCC_voidInit();
void MRCC_voidEnPeriphClk(u8 Copy_u8PeriphIdx);
void MRCC_voidDsPeriphClk(u8 Copy_u8PeriphIdx);

#endif
