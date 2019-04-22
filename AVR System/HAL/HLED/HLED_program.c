#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "MDIO_interface.h"


void HLED_init(u8 port, u8 pin){
	MDIO_setPinDirection(port, pin, OUTPUT);
}

void HLED_initLEDS(u8 port, u8 mask){
	MDIO_setPortDirection(port, mask, OUTPUT);
}

void HLED_on(u8 port, u8 pin){
	MDIO_setPinValue(port, pin, HIGH);
}

void HLED_onLEDS(u8 port, u8 mask){
	MDIO_setPort(port, mask);
}

void HLED_off(u8 port, u8 pin){
	MDIO_setPinValue(port, pin, LOW);
}

void HLED_offLEDS(u8 port, u8 mask){
	MDIO_clrPort(port, mask);
}

void HLED_toggle(u8 port, u8 pin){
    MDIO_togglePin(port, pin);
}

void HLED_toggleLEDS(u8 port, u8 mask){
	MDIO_setPortToValue(port,mask, port^mask);
}
