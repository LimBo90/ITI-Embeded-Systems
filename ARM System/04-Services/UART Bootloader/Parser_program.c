#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "LNUM_UTILS.h"

#include "Parser_private.h"
#include "Parser_interface.h"


typedef struct 
{
  u8 byte_count;
  u8 record_type;
  u32 data[8];
  u16 address;
}Record_t;

Record_t record;

/**
 * Parses HEX line and extracts byte_count, record_type, address and data
 * returns record status which can be either
 * RECORD_PARESE_OK,RECORD_COLON_ERR or RECORD_CC_ERR
 */
u8 Parser_u8ParseRecord(u8 * str){
    u8 status = RECORD_PARSE_OK;
    u8 i;
    u8 dataBytesCount = 0;
    u8 checkSum = 0;
    u8 addressMSB, addressLSB;
    //initaizes record
    Parser_voidResetRecord();
    if(str[0] == ':'){
        //if line starts with ':' 
        //porceed to recieve byte count
        i = 1;
        record.byte_count = LNUMUTILS_u8HexToByte(str+i);
        checkSum += record.byte_count;
        i += 2;

        //get address
        addressMSB = LNUMUTILS_u8HexToByte(str+i);
        i += 2;
        addressLSB = LNUMUTILS_u8HexToByte(str+i);
        i += 2;
        record.address = (((u16)addressMSB) << 8) | addressLSB;
        checkSum += addressMSB + addressLSB;

        //recieve record type
        record.record_type = LNUMUTILS_u8HexToByte(str+i);
        checkSum += record.record_type;
        i += 2;

        //recieve data bytes
        for(dataBytesCount = 0; dataBytesCount < record.byte_count; dataBytesCount++){
        	u8 dataIndx = dataBytesCount / 4;
        	u8 rem = 3 - (dataBytesCount % 4);
        	u8 dataByte = LNUMUTILS_u8HexToByte(str+i);
        	//put byte in its place in data array
        	record.data[dataIndx] &= ~((u32)0xFF << (rem * 8));
            record.data[dataIndx] |= ((u32)dataByte << (rem * 8)) ;
            checkSum += dataByte;
            i += 2;
        }
        //add checksum byte
        checkSum += LNUMUTILS_u8HexToByte(str+i);
        if(checkSum){
            //if the sum of all bytes including the checksum byte itself is not 0
            //this means a checksum error occurred
            status = RECORD_PARSE_ERR_CC;
        }
    }else{
        status = RECORD_PARSE_ERR_MISSING_COLON;
    }
    return status;
}

void Parser_voidResetRecord(){
	record.address = 0;
	record.byte_count = 0;
	record.record_type = 0;
	record.data[0] = 0xFFFFFFFF;
	record.data[1] = 0xFFFFFFFF;
	record.data[2] = 0xFFFFFFFF;
	record.data[3] = 0xFFFFFFFF;
	record.data[4] = 0xFFFFFFFF;
	record.data[5] = 0xFFFFFFFF;
	record.data[6] = 0xFFFFFFFF;
	record.data[7] = 0xFFFFFFFF;
	record.data[8] = 0xFFFFFFFF;
}


/**
 * Returns bytes count
 */
u8 Parser_u8GetBytesCount(void){
	return record.byte_count;
}

/**
 * Returns record type
 * Called after parsing the record
 */
u8 Parser_u8GetRecordType(void){
	return record.record_type;
}

/**
 * Returns data in record
 * Called after parsing the record
 */
u16 Parser_u8GetAddress(void){
	return record.address;
}

/**
 * Returns record's data
 * Called after parsing the record
 */
u32 * Parser_u32GetData(void){
	return record.data;
}

