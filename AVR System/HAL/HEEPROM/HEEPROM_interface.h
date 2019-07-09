/*
 * HEEPROM_interface.h
 *
 *  Created on: Jun 27, 2019
 *      Author: Abdelrahman
 */

#ifndef HEEPROM_INTERFACE_H_
#define HEEPROM_INTERFACE_H_

#define HEEPROM_ADDRESS 0x50

/**
 * Initalizes EEPROM by initalizing I2C communication
 */
void HEEPROM_voidInit(void);

/**
 * Writes a byte to a specific location in EEPROM
 */
void HEEPROM_voidWriteByte(u16 Copy_u16Location, u8 Copy_u8Byte);


void HEEPROM_voidReadByte(u16 Copy_u16Location, u8 * data);

#endif /* HEEPROM_INTERFACE_H_ */
