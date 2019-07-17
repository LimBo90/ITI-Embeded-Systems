/*
 * BootLoader_config.h
 *
 *  Created on: Jul 15, 2019
 *      Author: Abdelrahman
 */

#ifndef BOOTLOADER_CONFIG_H_
#define BOOTLOADER_CONFIG_H_

#define FLASH_START_ADDRESS 		(u32)0x08000000	/* Start address of the flash */
#define APP_OFFSET					(u32)0x5000		/* Offset of the application's start adress relative to flash start address */
#define APP_END_ADDRESS				(u32)0x0801FBFF	/* application end address */
#define BOOTLOADER_TIMEOUT_DURATION	(u32)0x00400000 /* timeout of bootloader after which the bootloader jumps to the application */

#endif /* BOOTLOADER_CONFIG_H_ */
