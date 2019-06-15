#ifndef _MUART_INTERFACE_H
#define _MUART_INTERFACE_H_

/**
 * Initalizes the UART module
 */
void MUART_voidInit(void);

/**
 * Sends a byte to the UART module
 */
void MUART_voidSendByte(u8 Copy_u8Data);

/**
 * Return 1 if there's a byte received through the UART module if nothing is received returns 0
 * Puts the received byte in Copy_u8Data
 */
u8 MUART_voidRecieveByte(u8 * Copy_u8Data);

#endif
