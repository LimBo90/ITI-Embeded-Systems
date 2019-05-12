#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

#include "HLCD_private.h"
#include "MDIO_interface.h"

#define HLCD_CONTROL_PORT PORTC
#define HLCD_RS	PIN_0
#define HLCD_RW	PIN_1
#define HLCD_EN	PIN_2
#define HLCD_DATA_PORT	PORTA


#define HLCD_MODE_8_BIT 1

#define HLCD_LEFT 0
#define HLCD_RIGHT 1

void HLCD_init(void);
void HLCD_writeCMD(u8 cmd);
void HLCD_writeData(u8 data);
void HLCD_writeStr(u8 str[]);
void HLCD_writeNumber(u16 n);
void HLCD_setCursor(u8 x, u8 y);
void HLCD_clearDisplay();
void HLCD_shiftCursor(u8 direction);
void HLCD_shiftDisplay(u8 direction);
void HLCD_addCustomCharacter(u8 indx, u8 pattern[7]);
void HLCD_displayCustomCharacter(u8 indx);

#endif
