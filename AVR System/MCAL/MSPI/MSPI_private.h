/*
 * MSPI_Private.h
 *
 *  Created on: Jun 16, 2019
 *      Author: Hamza
 */

#ifndef MSPI_PRIVATE_H_
#define MSPI_PRIVATE_H_

//SPCR Rigester PINS
#define MSPI_SPR0			0
#define MSPI_SPR1			1
#define MSPI_CPHA			2
#define MSPI_CPOL			3
#define MSPI_MSTR			4
#define MSPI_DORD			5
#define MSPI_SPE			6
#define MSPI_SPIE			7

//SPSR	Register Bits
#define MSPI_SPI2X			0
#define MSPI_WCOL			6
#define MSPI_SPIF			7


#define MSPI_SPDR 	 *((volatile u8*)(0x2F))

#define MSPI_SPSR    *((volatile u8*)(0x2E))

#define MSPI_SPCR    *((volatile u8*)(0x2D))



#endif /* MSPI_PRIVATE_H_ */
