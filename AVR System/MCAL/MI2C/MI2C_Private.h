/*
 * MI2C_Private.h
 *
 *  Created on: Jun 24, 2019
 *      Author: Hamza
 */

#ifndef MI2C_PRIVATE_H_
#define MI2C_PRIVATE_H_


#define MI2C_TWDR	  *((volatile u8*)(0x23))
#define MI2C_TWAR  	  *((volatile u8*)(0x22))
#define MI2C_TWSR     *((volatile u8*)(0x21))
#define MI2C_TWBR	  *((volatile u8*)(0x20))

#define MI2C_TWCR	  *((volatile u8*)(0x56))



#endif /* MI2C_PRIVATE_H_ */
