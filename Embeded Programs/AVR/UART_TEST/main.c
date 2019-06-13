#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "util/delay.h"
#include "MDIO_interface.h"
#include "MUART_interface.h"



int main(){
	u32 i;
	MUART_voidInit();
	while(1){
		MUART_voidSendByte('A');
		_delay_ms(1000);
		MUART_voidSendByte('B');
		_delay_ms(1000);
	}

	return 0;
}
