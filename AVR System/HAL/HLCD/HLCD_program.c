#define F_CPU 8000000

#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "util/delay.h"
#include "MDIO_interface.h"
#include "HLCD_interface.h"

void HLCD_init(void){
	//Sets control pins and data port pins to be output
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RS, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RW, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_EN, OUTPUT);
	if(HLCD_MODE_8_BIT)
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xFF, OUTPUT);
	else
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xF0, OUTPUT);
	_delay_ms(50);

	//Function set
	//sets the data length to 8bit or 4bit mode
	//sets the lcd to be 2 line display
	//sets the font to be 5 x 10 dots
	if(HLCD_MODE_8_BIT)
		HLCD_writeCMD(FNSET_DATA_LENGTH_8_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	else
		HLCD_writeCMD(FNSET_DATA_LENGTH_4_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	_delay_ms(1);

	//Display ON/OFF Control
	//sets the display to be ON
	//display the cursor
	//makes the cursor blink
	HLCD_writeCMD(DISPLAYCONTROL_DISPLAY_ON | DISPLAYCONTROL_CURSOR_ON | DISPLAYCONTROL_CURSOR_BLINK_ON);
	_delay_ms(1);

	//Clear Display
	HLCD_writeCMD(CLEAR_DISPLAY);
	_delay_ms(2);

	//sets the move direction of cursor and display
	//sets the cursor to move to the right when a new character is displayed and the new character is added to the left (left to right)
	//sets the display to shift
	HLCD_writeCMD(ENTRYMODE_LEFT_TO_RIGHT | ENTRYMODE_DISPLAY_SHIFT_OFF);
}

/**
 * Sends a command to the display
 */
void HLCD_writeCMD(u8 cmd){
	//sets RS = LOW to write in the command register
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_RS, LOW);
	//sets RW = LOW to write
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_RW, LOW);
	//sets EN = LOW preparing for the latch
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	if(HLCD_MODE_8_BIT){
		//writes the command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xFF, cmd);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	}else{
		//writes the upper 4 bits of command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);

		//writes the lower 4 bits command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd<<4);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	}
	return;
}

/**
 * Sends a character to be displayed
 */
void HLCD_writeData(u8 data){
	//sets RS = HIGH to write in the data register
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_RS, HIGH);
	//sets RW = LOW to write
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_RW, LOW);
	//sets EN = LOW preparing for the latch
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);

	if(HLCD_MODE_8_BIT){
		//writes the command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xFF, data);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	}else{
		//writes the upper 4 bits of data to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);

		//writes the lower 4 bits of data to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data<<4);

		//latches the EN pin
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
		_delay_ms(2);
		MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
	}
	return;
}

/**
 * Displays a string
 */
void HLCD_writeStr(u8 str[]){
	u8 i = 0;
	while(str[i] != '\0'){
		HLCD_writeData(str[i]);
		i++;
	}
}

