/*
 * UART_Interface.h
 *
 *  Created on: Jul 12, 2019
 *      Author: Hamza
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define MUART_COMPLETE 	0
#define MUART_TIMEOUT	1

void MUART_voidInit(void);

void MUART_voidSendChar(u8 copy_data);

void MUART_voidSendString(u8*);

/**
 * Receives a character through UART, blocks CPU until character is received or timeout.
 * Returns MUART_COMPLETE or MUART_TIMEOUT
 */
u8 MUART_u8ReceiveChar(u32 Copy_u32Timeout, u8 * data);

/**
 * Receives a string through UART, blocks CPU until string is received or timeout.
 * Returns MUART_COMPLETE or MUART_TIMEOUT
 */
u8 MUART_u8ReceiveString(u32 Copy_u32Timeout, u8 * str);


#endif /* UART_INTERFACE_H_ */
