#ifndef _PARSER_INTERFACE_H_
#define _PARSER_INTERFACE_H_


/****************** Record Parse status ********************************/
#define RECORD_PARSE_ERR_MISSING_COLON  12 	/* record doesn't start with ':'*/
#define RECORD_PARSE_ERR_CC       		14 	/* record checksum error*/
#define RECORD_PARSE_OK           		90	/* record received correctly*/


/******************* Record Types *****************************/
#define RECORD_TYPE_DATA 					0x00	/* data record */
#define RECORD_TYPE_EOF	 					0x01	/* end of file record */
#define RECORD_TYPE_EXTENDED_LINEAR_ADDRESS 0x04	/* 	extended linear address record which
														changes the upper 2 bytes of the flash address */
#define RECORD_TYPE_START_LINEAR_ADDRESS	0x05	/* this record type is for intel processors and ignored here */

/**
 * Parses string as hex record and extracts bytes coun, address, record type
 * and data.
 * Returns either RECORD_PARESE_OK, RECORD_CC_ERR or RECORD_COLON_ERROR
 */
u8 Parser_u8ParseRecord(u8 * str);


u8 Parser_u8DecodeRecord(u8 * str);

void Parser_voidRecieveRecord();

/**
 * Returns bytes count
 */
u8 Parser_u8GetBytesCount(void);

/**
 * Returns record type
 * Called after parsing the record
 */
u8 Parser_u8GetRecordType(void);

/**
 * Returns address in the record
 * Called after parsing the record
 */
u16 Parser_u8GetAddress(void);

/**
 * Returns data in record
 * Called after parsing the record
 */
u16 Parser_u8GetAddress(void);

/**
 * Returns record's data
 * Called after parsing the record
 */
u32 * Parser_u32GetData(void);


#endif // !_PARSER_H_

