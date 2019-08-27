#ifndef _MUART_INTERFACE_H
#define _MUART_INTERFACE_H_

/**
 * Initalizes the UART module
 */
void MUART_voidInit(void);

/**
 * Sends a byte through the UART module without polling (character is recorded in buffer and sent when UART is ready to transmit)
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendByte(u8 Copy_u8Data);

/**
 * Sends a byte through UART and doesnt return until that character is sent
 */
void MUART_voidSendBytePoling(u8 Copy_u8Data);

/**
 * Sends a string through the UART module
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendStr(u8 * str);

/**
 * Sends a number through the UART module
 * Return 1 if it has succeeded in sending the string
 * and 0 if the buffer is full.
 */
u8 MUART_u8SendNumber(u32 n);

/**
 * Return 1 if there's a byte received through the UART module if nothing is received returns 0
 * Puts the received byte in Copy_u8Data
 */
u8 MUART_u8RecieveByte(u8 * Copy_u8Data);

/**
 * Sets callback that's called when a receive interrupt happens
 */
void MUART_voidSetOnRecieveCallback(void (*func) (u8));

/**
 * prints the number of overflows and preload
 * used for debugging
 */
void MUART_voidSendBytePoling(u8 Copy_u8Data);

#endif
