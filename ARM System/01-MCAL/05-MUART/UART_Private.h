/*
 * UART_Private.h
 *
 *  Created on: Jul 12, 2019
 *      Author: Hamza
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


// USART_SR pins

#define CTS		9
#define LBD		8
#define TXE		7
#define TC		6
#define RXNE	5
#define IDLE	4
#define ORE		3
#define NE		2
#define FE		1
#define PE		0


// (USART_CR1) pins

#define UE		13
#define M		12
#define WAKE	11
#define PCE		10
#define	PS		9
#define PEIE	8
#define TXEIE	7
#define TCIE	6
#define RXNEIE	5
#define IDLEIE	4
#define TE		3
#define RE		2
#define RWU		1
#define SBK		0


// (USART_CR2)


#define LINEN		14
#define STOP1		13
#define STOP0		12
#define CLKEN		11
#define CPOL		10
#define CPHA		9
#define LBCL		8
#define LBDIE		6
#define LBDL		5
#define ADD3		3
#define ADD2		2
#define ADD1		1
#define ADD0		0


//(USART_CR3) pins

#define CTSIE		10
#define CTSE		9
#define RTSE		8
#define DMAT		7
#define DMAR		6
#define SCEN		5
#define NACK		4
#define HDSEL		3
#define IRLP		2
#define IREN		1
#define EIE			0

typedef struct
{
	u32 UART_SR;
	u32 UART_DR;
	u32 UART_BRR;
	u32 UART_CR1;
	u32 UART_CR2;
	u32 UART_CR3;
	u32 UART_GTPR;

}uart;

#define MUART_SR	*((u32*)(0x40013800))
#define MUART_DR	*((u32*)(0x40013804))
#define MUART_BRR	*((u32*)(0x40013808))
#define MUART_CR1	*((u32*)(0x4001380C))
#define MUART_CR2	*((u32*)(0x40013810))
#define MUART_CR3	*((u32*)(0x40013814))
#define MUART_GTPR	*((u32*)(0x40013818))

#endif /* UART_PRIVATE_H_ */
