#ifndef _MFLASH_INTERFACE_H
#define _MFLASH_INTERFACE_H

// FLASH States
#define MFLASH_BUSY 		1	//Flash operation is in progress
#define MFLASH_ERROR_PG		2	//Tried to program an address that's not previously erased (value different from 0xFFFF)
#define MFLASH_ERROR_WRP	3	//Tried to program a write protected address
#define MFLASH_COMPLETE		4	//Last operation completed successfully
#define MFLASH_TIMEOUT		5	//Flash took too much time to execute operation

/* Initalizes FLASH Interface. */
void MFLASH_voidInit(void);

/* Unlocks the  FLASH Program Erase Controller. */
void MFLASH_voidUnlock(void);

/* Locks the  FLASH Program Erase Controller. */
void MFLASH_voidLock(void);

/**
 * Returns the current Status of the FLASH
 * can either be MFLASH_BUSY, MFLASH_ERROR_PG,
 * MFLASH_ERROR_WRP, MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_voidGetStatus(void);

/**
 * Clears flash status flags PGERR, WRPRTERR and EOP flags
 */
void MFLASH_voidClearPendingFlags(void);

/**
 * Erases a page from the flash
 * input:	Copy_u8PageAddress Address of the page in FLASH to be erased
 * Returns the flash status, can either be
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8ErasePage(u32 Copy_u8PageAddress);

/**
 * Writes a word to a specific address in FLASH
 * input:	Copy_u32Address Address in FLASH to write the data into
 * 			Copy_u32Data 	Data to be written
 * Returns the flash status, can either be
 * MFLASH_BUSY, MFLASH_ERROR_PG, MFLASH_ERROR_WRP
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8WriteWord(u32 Copy_u32Address, u32 Copy_u32Data);

/**
 * Writes a half word (2 bytes) to a specific address in FLASH
 * input:	Copy_u32Address Address in FLASH to write the data into
 * 			Copy_u16Data 	Data to be written
 * Returns the flash status, can either be
 * MFLASH_BUSY, MFLASH_ERROR_PG, MFLASH_ERROR_WRP
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8WriteHalfWord(u32 Copy_u32Address, u16 Copy_u16Data);
#endif
