/*
 * Bootloader_program.c
 *
 *  Created on: Jul 15, 2019
 *      Author: Abdelrahman
 */

#include "LSTD_TYPES.h"
#include "MRCC_interface.h"
#include "MDIO_interface.h"

#include "MFLASH_interface.h"
#include "UART_Interface.h"

#include "Parser_interface.h"
#include "BootLoader_config.h"
#include "BootLoader_private.h"
#include "BootLoader_interface.h"

typedef enum{
	Waiting,	/* Waiting for either a timeout or recieving a hex line through UART */
	WritingApp,	/* In this state the bootloader is writing application to flash as it's recieved line by line through UART*/
	Finished	/* In this state the bootloader has finished and ready to jump to application */
}BootLoader_State;

/* Current state of the bootloader */
BootLoader_State currentBLState;

/* application ready in flash flag */
u8 	appReady = 0;

/* the most significant 4 bytes of the current flash address */
u32 currentAddressMSB = 0x8000000;

/**
 * Initializes bootloader
 */
void BootLoader_voidInit(){
	MRCC_voidInit();
	MRCC_voidEnPeriphClk(MRCC_U8_USART1);
	MRCC_voidEnPeriphClk(MRCC_U8_FLITF);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOA);
	MRCC_voidEnPeriphClk(MRCC_U8_GPIOC);
	//intalize UART pins
	MDIO_voidSetPinMode(MDIO_PORTA, MDIO_PIN_9, MDIO_MODE_AF_OUTPUT_PUSHPULL_2);
	MDIO_voidSetPinMode(MDIO_PORTA,	MDIO_PIN_10,	MDIO_MODE_INPUT_FLOATING);
	//LED indicating bootloader is active
	MDIO_voidSetPinMode(MDIO_PORTC,MDIO_PIN_13,MDIO_MODE_OUTPUT_PUSHPULL_2);
	MDIO_voidSetPinValue(MDIO_PORTC,MDIO_PIN_13,DIO_U8_LOW);

	MFLASH_voidInit();
	MUART_voidInit();

	/* Initalizes state of bootloader */
	currentBLState = Waiting;

	/* Checks if application exists in flash*/
	appReady = BootLoader_u8AppExists();
}

/**
 * Bootloader finite state machine
 */
void BootLoader_voidFSM(){
	u8 status = RECORD_OK;
	static u8 hexLine[50];

	switch(currentBLState){
		case Waiting:
			MUART_voidSendString("LOG: Waiting\r");
			/* Receive hex line through UART */
			status = MUART_u8ReceiveString(BOOTLOADER_TIMEOUT_DURATION, hexLine);

			if(status == MUART_COMPLETE){
			/* if received correctly erase application region in flash */
				MUART_voidSendString("LOG: New hex file incoming \r");
				MUART_voidSendString("LOG: Erasing FLASH...\r");
				status = BootLoader_u8EraseApplicationFlash();
				if(status == MFLASH_COMPLETE){
					/* application region erased successfully */
					currentBLState = WritingApp; /* move to writing state */
					appReady = 0;	/*Signal that the application isn't ready*/
				}else{
					/* Error during erasing application region */
					BootLoader_voidSendError(RECORD_FLASH_ERR_ERASE);
				}
			}else if(status == MUART_TIMEOUT && appReady){
				/* if timeout occurred and an application is already ready in flash move to finished state */
				currentBLState = Finished;
			}else{
				/* anything else stay in waiting state */
				currentBLState = Waiting;
			}
			break;

		case WritingApp:
			/* Parse received hex line into record */
			status = Parser_u8ParseRecord(hexLine);

			if(status == RECORD_PARSE_OK){
				/* if record is parsed correctly. start decoding record */
				status = BootLoader_u8DecodeRecord();

				if(status == RECORD_EOF){
					/* send ok */
					MUART_voidSendString("ok\r");
					/* if finished writing hex file	signal that the application is ready */
					appReady = 1;
					/* move to finished state */
					currentBLState = Finished;
				}
			}

			if(status != RECORD_OK && status != RECORD_EOF ){
				/* if record parsed or decoded incorrectly */
				BootLoader_voidSendError(status);	/* sends error status */

				/* if error is due to flash clear its error flags */
				if(status == RECORD_FLASH_ERR_PG || status == RECORD_FLASH_ERR_WRP)
					MFLASH_voidClearPendingFlags();

				/* Move to waiting state*/
				currentBLState = Waiting;
			}

			if(currentBLState == WritingApp){
				MUART_voidSendString("ok\r");
				/* Receive next hex line through UART */
				status = MUART_u8ReceiveString(BOOTLOADER_TIMEOUT_DURATION, hexLine);
				if(status == MUART_COMPLETE){
					/* if hex line received correctly stay in writing state */
					currentBLState = WritingApp;
				}else if(status == MUART_TIMEOUT){
					/* if timeout move report through UART and return to waiting state */
					MUART_voidSendString("ERR: Timeout waiting for next hex line.\r");
					MFLASH_voidClearPendingFlags();
					currentBLState = Waiting;
				}
			}
			break;
	}
}

/**
 * Starts bootloader
 * Blocks  CPU until an app is ready in flash.
 * if an app already exits in flash waits timeout period to recieve a new app
 */
void BootLoader_voidStart(){
	if(appReady)
		MUART_voidSendString("LOG: Application detected in FLASH\r");
	else
		MUART_voidSendString("LOG: No application detected in FLASH\r");

	do{
		BootLoader_voidFSM();
	}while(currentBLState != Finished);

	MUART_voidSendString("LOG: BootLooder finished execution \r");
	BootLoader_voidExit();

}


/**
 * prepare to exit from bootloader
 * Deinit all peripherals used by bootloader
 */
void BootLoader_voidExit(){

	MUART_voidSendString("LOG: BootLoader Exiting...\r");


	MFLASH_voidLock();
	MDIO_voidSetPinValue(MDIO_PORTC, MDIO_PIN_13, DIO_U8_HIGH);

	MRCC_voidDsPeriphClk(MRCC_U8_USART1);
	MRCC_voidDsPeriphClk(MRCC_U8_FLITF);
	MRCC_voidDsPeriphClk(MRCC_U8_GPIOA);
	MRCC_voidDsPeriphClk(MRCC_U8_GPIOC);

	/* jump to aplication */
	BootLoader_voidJumpToApp();
}

/**
 * jump to application
 */
void BootLoader_voidJumpToApp(){
	SCB_VTOR = (APP_OFFSET) << 8; //relocate vector table
	void (*ptr)(void);
	ptr = (void (*)(void))(*(volatile u32*) (FLASH_START_ADDRESS + APP_OFFSET + 4));
	ptr();
}

/**
 * Erases application region in Flash
 * Returns either MFLASH_COMPLETE or MFLASH_TIMEOUT
 */
u8 BootLoader_u8EraseApplicationFlash(){
	u8 status;
	u32 pageAddress;

	for(pageAddress = FLASH_START_ADDRESS + APP_OFFSET; pageAddress < APP_END_ADDRESS; pageAddress += 0x400){
		status = MFLASH_u8ErasePage(pageAddress);
		if(status != MFLASH_COMPLETE)
			break;
	}

	return status;
}


/**
 * Decodes record and calls handler based on record type
 *	Returns either RECORD_EOF, RECORD_FLASH_ERR_PG, RECORD_FLASH_ERR_WRP,
 *	RECORD_FLASH_ERR_TIMEOUT  RECORD_FLASH_ERR_INVALID_ADD or RECORD_OK
 *
 */
u8 BootLoader_u8DecodeRecord(){
	u8 status = RECORD_OK;
	switch(Parser_u8GetRecordType()){
		case RECORD_TYPE_DATA:
			/* data record to be written to flash */
			status = BootLoader_u8DataRecordHandler();
			break;
		case RECORD_TYPE_EXTENDED_LINEAR_ADDRESS:
			/* extended linear address record to set the higher 2 bytes of current address */
			BootLoader_voidLinearAddressHandler();
			status = RECORD_OK;
			break;
		case RECORD_TYPE_EOF:
			/** end of file record */
			status = RECORD_EOF;
			break;
		case RECORD_TYPE_START_LINEAR_ADDRESS:
			/* start linear address record is ignored here ie. no action is taken */
			status = RECORD_OK;
			break;
		default:
			/* Unknown record type */
			status = RECORD_UNKNOWN_TYPE_ERR;
			break;
	}
	return status;
}

/**
 * handles data record and writes it to FLASH
 * Returns RECORD_OK, RECORD_FLASH_PG_ERR, RECORD_FLASH_TIMEOUT_ERR
 * or RECORD_FLASH_WRP_ERR
 */
u8 BootLoader_u8DataRecordHandler(){
	u8 status = RECORD_OK;
	//calculate number of words(4 byte) in data
	u8 nWords = Parser_u8GetBytesCount() / 4;
	u8 nRemainingBytes = Parser_u8GetBytesCount() % 4;
	u8 i = 0;
	u32 address = (currentAddressMSB | (u32)Parser_u8GetAddress());
	u32 * data = Parser_u32GetData();

	if(nRemainingBytes > 0){
		nWords++;
	}

	for(i = 0; i <nWords; i++){
		if( address < FLASH_START_ADDRESS + APP_OFFSET || address > APP_END_ADDRESS){
			status =  RECORD_FLASH_ERR_INVALID_ADD;
			break;
		}
		//convert data to little endian presentation
		u32 littleEndianData =  __builtin_bswap32(data[i]);
		status = MFLASH_u8WriteWord(address, littleEndianData);
		if(status != MFLASH_COMPLETE)
			break;
		address += 4;
	}

	if(status == MFLASH_COMPLETE)
		status = RECORD_OK;

	return status;
}

/**
 * handles extended linear address record which changes the upper 2 bytes
 * of the current flash address
 * Returns either RECORD_OK, or RECORD_FLASH_INVALID_ADD
 */
u8 BootLoader_voidLinearAddressHandler(){
	u8 status = RECORD_OK;
	currentAddressMSB = Parser_u32GetData()[0] & 0xFFFF0000;
	if(currentAddressMSB < FLASH_START_ADDRESS + APP_OFFSET || currentAddressMSB > APP_END_ADDRESS){
		status = RECORD_FLASH_ERR_INVALID_ADD;
	}
	return status;
}

u8 BootLoader_u8AppExists(){
	u32 appJumpLocation = *((volatile u32*) (FLASH_START_ADDRESS + APP_OFFSET + 4));
	return appJumpLocation != 0xFFFFFFFF;
}

/**
 * Send error through UART
 */
void BootLoader_voidSendError(u8 errorCode){
	switch(errorCode){
		case RECORD_PARSE_ERR_CC:				MUART_voidSendString("ERR: Checksum error\r");																	break;
		case RECORD_PARSE_ERR_MISSING_COLON:	MUART_voidSendString("ERR: Invalid record. Missing ':' at beginning of record\r");									break;
		case RECORD_FLASH_ERR_PG:				MUART_voidSendString("ERR: Couldn't write record to flash. Tried to write into a region not previously erased\r");	break;
		case RECORD_FLASH_ERR_WRP:				MUART_voidSendString("ERR: Couldn't write record to flash. Tried to write into a write protected region\r");		break;
		case RECORD_FLASH_ERR_TIMEOUT:			MUART_voidSendString("ERR: Couldn't complete flash. Flash took too long to program(timeout error).\r");		break;
		case RECORD_FLASH_ERR_INVALID_ADD:		MUART_voidSendString("ERR: Couldn't write record to flash. Invalid address for record.\r");							break;
		case RECORD_UNKNOWN_TYPE_ERR: 			MUART_voidSendString("ERR: Record has an unknown type field\r");												break;
		case RECORD_FLASH_ERR_ERASE:			MUART_voidSendString("ERR: Couldn't erase application region in flash. (timeout error)\r");						break;
		default:								MUART_voidSendString("ERR: Undefined Status\r"); 																break;
	}
}


