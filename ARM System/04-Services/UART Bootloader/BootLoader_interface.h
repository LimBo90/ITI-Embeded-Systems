/*
 * BootLoader_interface.h
 *
 *  Created on: Jul 15, 2019
 *      Author: Abdelrahman
 */

#ifndef BOOTLOADER_INTERFACE_H_
#define BOOTLOADER_INTERFACE_H_


/****************** Record Decoding status ******************************/
#define RECORD_OK           			0					/* record received correctly*/
#define RECORD_EOF						10					/* end of file record*/
#define RECORD_UNKNOWN_TYPE_ERR			20 					/* record type code is unknown*/
#define RECORD_FLASH_ERR_PG				MFLASH_ERROR_PG 	/* record failed to be written to flash due to page error*/
#define RECORD_FLASH_ERR_WRP			MFLASH_ERROR_WRP 	/* record failed to be written to flash due to write protection*/
#define RECORD_FLASH_ERR_TIMEOUT		MFLASH_TIMEOUT 		/* record failed to be written to flash	due to timeout*/
#define RECORD_FLASH_ERR_INVALID_ADD	30					/* record's address in not in the range of application flash */


/**
 * Initalizes bootloader
 */
void BootLoader_voidInit();


/**
 * Starts bootloader
 * Blocks  CPU until an app is ready in flash.
 * if an app already exits in flash waits timeout period to recieve a new app
 */
void BootLoader_voidStart();



#endif /* BOOTLOADER_INTERFACE_H_ */
