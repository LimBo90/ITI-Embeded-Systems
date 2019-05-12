

#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "util/delay.h"
#include "MDIO_interface.h"
#include "HLCD_interface.h"

void latchEnablePin(u8 delay);
void numberToString(s32 i, u8 buff[]);


void HLCD_init(void){
	_delay_ms(30);
	//Sets control pins and data port pins to be output
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RS, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RW, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_EN, OUTPUT);
	if(HLCD_MODE_8_BIT)
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xFF, OUTPUT);
	else
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xF0, OUTPUT);
	_delay_ms(1);

	//Function set
	//sets the data length to 8bit or 4bit mode
	//sets the lcd to be 2 line display
	//sets the font to be 5 x 10 dots
	if(HLCD_MODE_8_BIT){
		HLCD_writeCMD(FNSET_DATA_LENGTH_8_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	}else{
		//writes the upper 4 bits of command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, 0x20);
		latchEnablePin(2);
		HLCD_writeCMD(FNSET_DATA_LENGTH_4_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	}
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
		latchEnablePin(2);
	}else{
		//writes the upper 4 bits of command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd);
		latchEnablePin(2);

		//writes the lower 4 bits command to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd<<4);
		latchEnablePin(2);
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
		latchEnablePin(2);
	}else{
		//writes the upper 4 bits of data to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data);
		latchEnablePin(2);

		//writes the lower 4 bits of data to the data port
		MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data<<4);
		latchEnablePin(2);
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

void HLCD_writeNumber(u16 n){
	u8 buffer[16];
	numberToString(n, buffer);
	HLCD_writeStr(buffer);
}

void HLCD_clearDisplay(){
	HLCD_writeCMD(CLEAR_DISPLAY);
}

void HLCD_setCursor(u8 row, u8 col){
	//The ranges are from 0 to 1 on the y-axis and from 0 to 15 on the x-axis
	if(!(row <= 1 && row >= 0 && col >= 0 && col <= 15))
		return;
	switch(row){
	case 0:
		//first line
		HLCD_writeCMD(col| DDRAM_FIRST_LINE_START_ADDRESS);
		break;
	case 1:
		//second line
		HLCD_writeCMD(col | DDRAM_SECOND_LINE_START_ADDRESS);
		break;
	}
	return;
}


void HLCD_shiftCursor(u8 direction){
	switch(direction){
	case HLCD_LEFT:
		HLCD_writeCMD(SHIFT_CURSOR_LEFT);
		break;
	case HLCD_RIGHT:
		HLCD_writeCMD(SHIFT_CURSOR_RIGHT);
		break;
	}
}

void HLCD_shiftDisplay(u8 direction){
	switch(direction){
	case HLCD_RIGHT:
		HLCD_writeCMD(SHIFT_DISPLAY_LEFT);
		break;
	case HLCD_LEFT:
		HLCD_writeCMD(SHIFT_DISPLAY_RIGHT);
		break;
	}
}


void HLCD_addCustomCharacter(u8 indx, u8 pattern[7]){
	//only 8 custom characters can be written from indx 0 to 7
	if(indx < 0 || indx > 7)
		return;

	//set address counter to CGRAM address
	u8 cgramAddress = indx * 8;
	HLCD_writeCMD(SET_CGRAM_ADDRESS_CMD | cgramAddress);
	for(int i = 0; i < 7; i++){
		HLCD_writeData(pattern[i]);
	}
	//the 8th row must be all zeroes
	HLCD_writeData(0);
	//sets the address counter back to ddram
	HLCD_writeCMD(DDRAM_FIRST_LINE_START_ADDRESS);
}

void HLCD_displayCustomCharacter(u8 indx){
	HLCD_writeData(indx);
}

void latchEnablePin(u8 delay){
	//latches the EN pin
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, HIGH);
	_delay_ms(delay);
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
}


void numberToString(s32 i, u8 b[]){
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = '0' + (i%10);
        i = i/10;
    }while(i);
}
