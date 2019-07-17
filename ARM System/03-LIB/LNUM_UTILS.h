
#ifndef _LNUM_UTILS_H_
#define _LNUM_UTILS_H_

/**
 * Converts a single hex digit to decimal
 */
u8 LNUMUTILS_u8HexToDec(u8 c);

/**
 * Converts 2 hex digits to decimal
 */
u8 LNUMUTILS_u8HexToByte(u8 str[2]);

#endif