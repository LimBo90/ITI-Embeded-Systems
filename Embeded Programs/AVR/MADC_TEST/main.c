/*
 * main.c
 *
 *  Created on: Jul 10, 2019
 *      Author: Abdelrahman
 */
#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "LDelay.h"

#include "MUART_interface.h"
#include "MADC_interface.h"

void sendResult(u16 res){
	MUART_u8SendNumber(res);
	MUART_u8SendByte('\n');
	MADC_voidStartConversionAsynch(sendResult);
}

void main(){
	MUART_voidInit();
	MADC_voidInit();

	MADC_voidSetChannel(MADC_ADC0);
	MADC_voidStartConversionAsynch(sendResult);
	while(1){
	}
}

