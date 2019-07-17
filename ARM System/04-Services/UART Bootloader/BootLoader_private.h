/*
 * BootLoader_private.h
 *
 *  Created on: Jul 15, 2019
 *      Author: Abdelrahman
 */

#ifndef BOOTLOADER_PRIVATE_H_
#define BOOTLOADER_PRIVATE_H_

#define SCB_VTOR (*(u32 *)(0xE000ED08))

/**
 * Erases application region in Flash
 */
u8 BootLoader_u8EraseApplicationFlash();


/**
 * Decodes record and calls handler based on record type
 *	Returns either RECORD_EOF, RECORD_FLASH_ERR_PG, RECORD_FLASH_ERR_WRP,
 *	RECORD_FLASH_ERR_TIMEOUT or RECORD_OK
 *
 */
u8 BootLoader_u8DecodeRecord();

/**
 * handles data record and writes it to FLASH
 * Returns RECORD_OK, RECORD_FLASH_PG_ERR, RECORD_FLASH_TIMEOUT_ERR
 *  or RECORD_FLASH_WRP_ERR
 */
u8 BootLoader_u8DataRecordHandler();

/**
 * handles extended linear address record which changes the upper 2 bytes
 * of the current flash address
 * Returns RECORD_OK or RECORD_FLASH_ERR_INVALID_ADD
 */
u8 BootLoader_voidLinearAddressHandler();

/**
 * Sends a Error through UART
 */
void BootLoader_voidSendError(u8 errorCode);


/**
 * Checks if there's an application already exists in flash
 */
u8 BootLoader_u8AppExists();


/**
 * prepare to exit from bootloader
 * Deinit all peripherals used by bootloader
 */
void BootLoader_voidExit();

/**
 * jump to application
 */
void BootLoader_voidJumpToApp();


#endif /* BOOTLOADER_PRIVATE_H_ */
