/*
 * MI2C_Interface.h
 *
 *  Created on: Jun 24, 2019
 *      Author: Hamza
 */

#ifndef MI2C_INTERFACE_H_
#define MI2C_INTERFACE_H_

//registers pin names
//TWCR
#define TWIE					0
#define TWEN					2
#define TWWC					3
#define TWSTO					4
#define TWSTA					5
#define TWEA					6
#define TWINT					7

//TWSR
#define TWPS0					0
#define TWPS1					1

//TWAR
#define TWGCE					0

#define MI2C_OPERATION_WRITE 0
#define MI2C_OPERATION_READ 1

void MI2C_voidInit(void);

void MI2C_voidStartCondition(void);

void MI2C_voidStopCondtion(void);

u8 MI2C_u8CheckStatus(u8 ExpectedStatus);

void MI2C_voidSendSlaveAddress(u8 SLA,u8 Operation);

void MI2C_voidSendData(u8 Data);

u8 MI2C_u8ReceiveDataWithNoAck();


#endif /* MI2C_INTERFACE_H_ */
