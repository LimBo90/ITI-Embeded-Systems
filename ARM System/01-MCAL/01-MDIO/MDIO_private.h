#ifndef _MDIO_PRIVATE_H_
#define _MDIO_PRIVATE_H_


typedef struct{
	u64 CR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
}GPIO;

#define MDIO_GPIOA	((volatile GPIO *) 0x40010800)
#define MDIO_GPIOB	((volatile GPIO *) 0x40010C00)
#define MDIO_GPIOC	((volatile GPIO *) 0x40011000)

#define DIO_U8_PORT_SIZE 	16
#define DIO_U8_PORTA	0
#define DIO_U8_PORTB	1
#define DIO_U8_PORTC	2

#endif
