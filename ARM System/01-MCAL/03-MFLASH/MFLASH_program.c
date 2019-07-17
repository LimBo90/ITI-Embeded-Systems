#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MFLASH_private.h"
#include "MFLASH_interface.h"


/* Initalizes FLASH Interface. */
void MFLASH_voidInit(void){
    MFLASH_voidUnlock();
}

/* Unlocks the  FLASH Program Erase Controller. */
void MFLASH_voidUnlock(void){
    if(LUTILS_GET_BIT(MFLASH->CR, LOCK)){
        MFLASH->KEYR = FLASH_KEY1;
        MFLASH->KEYR = FLASH_KEY2;
    }
}

/* Locks the  FLASH Program Erase Controller. */
void MFLASH_voidLock(void){
     LUTILS_SET_BIT(MFLASH->CR, LOCK);
}


/**
 * Returns the current Status of the FLASH
 * can either be MFLASH_BUSY, MFLASH_ERROR_PG,
 * MFLASH_ERROR_WRP, MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_voidGetStatus(void){
	u8 status;
	if(LUTILS_GET_BIT(MFLASH->SR, BSY))
		status = MFLASH_BUSY;
	else if(LUTILS_GET_BIT(MFLASH->SR, PGERR))
		status = MFLASH_ERROR_PG;
	else if(LUTILS_GET_BIT(MFLASH->SR, WRPRTERR))
		status = MFLASH_ERROR_WRP;
	else
		status = MFLASH_COMPLETE;
	return status;
}

/**
 * Clears flash status flags PGERR, WRPRTERR and EOP flags
 */
void MFLASH_voidClearPendingFlags(void){
	MFLASH->SR = 0b110100;
}

/**
 * Waits until the currently executing operation finishes
 * Returns the flash status, can either be
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_voidWaitForLastoperation(u32 timeout){
	u8 status = MFLASH_voidGetStatus();
	while(status == MFLASH_BUSY && timeout){
		status = MFLASH_voidGetStatus();
		timeout--;
	}
	if(!timeout)
		status = MFLASH_TIMEOUT;
	return status;
}

/**
 * Erases a page from the flash
 * input:	Copy_u8PageAddress Address of the page in FLASH to be erased
 * Returns the flash status, can either be
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8ErasePage(u32 Copy_u8PageAddress){
    //wait until current flash operation finishes
	u8 status = MFLASH_voidWaitForLastoperation(ERASE_TIMEOUT);

	if(status == MFLASH_COMPLETE){

	    //if the flash finishes previous operation erase the page
	    LUTILS_SET_BIT(MFLASH->CR, PER);
	    MFLASH->AR = Copy_u8PageAddress;
	    LUTILS_SET_BIT(MFLASH->CR, STRT);

	    //wait until erase operation finishes
		status = MFLASH_voidWaitForLastoperation(ERASE_TIMEOUT);

	    //disable the PER bit
	    LUTILS_CLR_BIT(MFLASH->CR, PER);

	}
    return status;
}

/**
 * Writes a word (4 bytes) to a specific address in FLASH
 * input:	Copy_u32Address Address in FLASH to write the data into
 * 			Copy_u32Data 	Data to be written
 * Returns the flash status, can either be
 * MFLASH_BUSY, MFLASH_ERROR_PG, MFLASH_ERROR_WRP
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8WriteWord(u32 Copy_u32Address, u32 Copy_u32Data){
	//wait until current flash operation finishes
	u8 status = MFLASH_voidWaitForLastoperation(ERASE_TIMEOUT);

	if(status == MFLASH_COMPLETE){
		 // if the previous operation is finished correctly, begin programming FLASH
		LUTILS_SET_BIT(MFLASH->CR, PG);

		//write LSB
		*(u16 *) Copy_u32Address = (u16)Copy_u32Data;
		//wait for the last operation to be completed
		status = MFLASH_voidWaitForLastoperation(PROGRAM_TIMEOUT);

		if(status == MFLASH_COMPLETE){
			//if the previous operation is completed successfully write the next 2 bytes
			*(u16 *) (Copy_u32Address + 2) = (u16)(Copy_u32Data >> 16);

			//wait for the last operation to be completed
			status = MFLASH_voidWaitForLastoperation(PROGRAM_TIMEOUT);

			//clear PG flag
			LUTILS_CLR_BIT(MFLASH->CR, PG);
		}else{
			LUTILS_CLR_BIT(MFLASH->CR, PG);
		}
	}
	return status;
}

/**
 * Writes a half word (2 bytes) to a specific address in FLASH
 * input:	Copy_u32Address Address in FLASH to write the data into
 * 			Copy_u16Data 	Data to be written
 * Returns the flash status, can either be
 * MFLASH_BUSY, MFLASH_ERROR_PG, MFLASH_ERROR_WRP
 * MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 MFLASH_u8WriteHalfWord(u32 Copy_u32Address, u16 Copy_u16Data){
	//wait until current flash operation finishes
	u8 status = MFLASH_voidWaitForLastoperation(ERASE_TIMEOUT);

	if(status == MFLASH_COMPLETE){
		 // if the previous operation is finished correctly, begin programming FLASH
		LUTILS_SET_BIT(MFLASH->CR, PG);

		//write LSB
		*(u16 *) Copy_u32Address = (u16)Copy_u16Data;
		//wait for the last operation to be completed
		status = MFLASH_voidWaitForLastoperation(PROGRAM_TIMEOUT);

		LUTILS_CLR_BIT(MFLASH->CR, PG);
	}
	return status;
}
