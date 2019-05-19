#ifndef _MDIO_PRIVATE_H_
#define _MDIO_PRIVATE_H_

#define MDIO_GPIOA_CRL	*((u32 *) (0x40010800))
#define MDIO_GPIOA_CRH	*((u32 *) (0x40010804))
#define MDIO_GPIOA_IDR	*((u32 *) (0x40010808))
#define MDIO_GPIOA_ODR	*((u32 *) (0x4001080C))

#define MDIO_GPIOB_CRL	*((u32 *) (0x40010C00))
#define MDIO_GPIOB_CRH	*((u32 *) (0x40010C04))
#define MDIO_GPIOB_IDR	*((u32 *) (0x40010C08))
#define MDIO_GPIOB_ODR	*((u32 *) (0x40010C0C))

#define MDIO_GPIOC_CRH	*((u32 *) (0x40011004))
#define MDIO_GPIOC_IDR	*((u32 *) (0x40011008))
#define MDIO_GPIOC_ODR	*((u32 *) (0x4001100C))



#define DIO_U8_PORT_SIZE 	16
#define DIO_U8_PORTA	0
#define DIO_U8_PORTB	1
#define DIO_U8_PORTC	2
#endif
