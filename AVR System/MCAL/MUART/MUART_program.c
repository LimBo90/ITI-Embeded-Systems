#include "LSTD_TYPES.h"
#include "LUTILS.h"

#include "MUART_private.h"
#include "MUART_interface.h"

void MUART_voidInit(void){
    SET_BIT(MUART_UCSRB, 4);    //enable RXEN
    SET_BIT(MUART_UCSRB, 3);    //enable TXEN

    CLR_BIT(MUART_UCSRB, 2);    //8bit 
    CLR_BIT(MUART_UCSRC, 2);
    CLR_BIT(MUART_UCSRC, 1);

    CLR_BIT(MUART_UCSRC, 6);    //Asynch

    CLR_BIT(MUART_UCSRC, 5);    //No parity
    CLR_BIT(MUART_UCSRC, 4);

    CLR_BIT(MUART_UCSRC, 3);    //1 stop bit

    MUART_UBRRH = 0;
    MUART_UBRRL = 51;
}

void MUART_voidSendByte(u8 Copy_u8Data){
    while(GET_BIT(MUART_UCSRA, 5) == 0);
    MUART_UDR = Copy_u8Data;
}

u8 MUART_voidRecieveByte(void){
    while(GET_BIT(MUART_UCSRA, 7) == 0);
    return MUART_UDR;
}

