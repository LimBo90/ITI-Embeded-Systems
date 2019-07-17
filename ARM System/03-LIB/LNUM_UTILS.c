#include "LSTD_TYPES.h"
#include "LNUM_UTILS.h"

/**
 * Converts a single hex digit to decimal
 */
u8 LNUMUTILS_u8HexToDec(u8 c){
    u8 res;
    if(c >= '0' && c <= '9')
        res = c - '0';
    else
        res = c - 55;
    return res;
}

/**
 * Converts 2 hex digits to decimal
 */
u8 LNUMUTILS_u8HexToByte(u8 str[2]){
    return LNUMUTILS_u8HexToDec(str[0]) * 16 + LNUMUTILS_u8HexToDec(str[1]);
}

