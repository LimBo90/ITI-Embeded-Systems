

#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "LDelay.h"
#include "MDIO_interface.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"
#include "HLCD_config.h"


static void latchEnablePin(u8 delay);
static void numberToString(u64 i, u8 buff[]);


void HLCD_init(void){
	LDelay_ms(30);
	//Sets control pins and data port pins to be output
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RS, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_RW, OUTPUT);
	MDIO_setPinDirection(HLCD_CONTROL_PORT, HLCD_EN, OUTPUT);
#if HLCD_MODE == HLCD_MODE_8_BIT
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xFF, OUTPUT);
#elif HLCD_MODE == HLCD_MODE_4_BIT
		MDIO_setPortDirection(HLCD_DATA_PORT, 0xF0, OUTPUT);
	LDelay_ms(1);
#else
	#error "HLCD_MODE not specified correctly in HLCD_config.h. Please set to either HLCD_MODE_8_BIT or HLCD_MODE_4_BIT"
#endif


	//Function set
	//sets the data length to 8bit or 4bit mode
	//sets the lcd to be 2 line display
	//sets the font to be 5 x 10 dots

#if HLCD_MODE == HLCD_MODE_8_BIT
	HLCD_writeCMD(FNSET_DATA_LENGTH_8_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
#elif HLCD_MODE == HLCD_MODE_4_BIT
	//writes the upper 4 bits of command to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, 0x20);
	latchEnablePin(2);
	HLCD_writeCMD(FNSET_DATA_LENGTH_4_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
#else
	#error "HLCD_MODE not specified correctly in HLCD_config.h. Please set to either HLCD_MODE_8_BIT or HLCD_MODE_4_BIT"
#endif

	//Display ON/OFF Control
	//sets the display to be ON
	//display the cursor
	//makes the cursor blink

#if HLCD_CURSOR_MODE != HLCD_CURSOR_ON && HLCD_CURSOR_MODE != HLCD_CURSOR_OFF
#error "HLCD_CURSOR_MODE not specified correctly in HCD_config.h. Please setto either HLCD_CURSOR_ON or HLCD_CURSOR_off"
#endif

#if HLCD_CURSOR_BLINK != HLCD_CURSOR_BLINK_OFF && HLCD_CURSOR_MODE != HLCD_CURSOR_BLINK_ON
#error "HLCD_CURSOR_MODE not specified correctly in HCD_config.h. Please setto either HLCD_CURSOR_BLINK_ON or HLCD_CURSOR_BLINK_OFF"
#endif
	HLCD_writeCMD(DISPLAYCONTROL_DISPLAY_ON | HLCD_CURSOR_MODE | HLCD_CURSOR_BLINK);
	LDelay_ms(1);

	//Clear Display
	HLCD_writeCMD(CLEAR_DISPLAY);
	LDelay_ms(2);

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

#if HLCD_MODE == HLCD_MODE_8_BIT
	//writes the command to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xFF, cmd);
	latchEnablePin(2);
#elif HLCD_MODE == HLCD_MODE_4_BIT
	//writes the upper 4 bits of command to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd);
	latchEnablePin(2);

	//writes the lower 4 bits command to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, cmd<<4);
	latchEnablePin(2);
#else
	#error "HLCD_MODE not specified correctly in HLCD_config.h. Please set to either HLCD_MODE_8_BIT or HLCD_MODE_4_BIT"
#endif
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

#if HLCD_MODE == HLCD_MODE_8_BIT
	//writes the command to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xFF, data);
	latchEnablePin(2);
#elif HLCD_MODE == HLCD_MODE_4_BIT
	//writes the upper 4 bits of data to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data);
	latchEnablePin(2);

	//writes the lower 4 bits of data to the data port
	MDIO_setPortToValue(HLCD_DATA_PORT, 0xF0, data<<4);
	latchEnablePin(2);
#else
	#error "HLCD_MODE not specified correctly in HLCD_config.h. Please set to either HLCD_MODE_8_BIT or HLCD_MODE_4_BIT"
#endif
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

void HLCD_writeNumber(u64 n){
	u8 buffer[20];
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


void HLCD_shiftCursorLeft(u8 n){
	for(; n > 0; n--)
		HLCD_writeCMD(SHIFT_CURSOR_LEFT);
}

void HLCD_shiftCursorRight(u8 n){
	for(; n > 0; n--)
		HLCD_writeCMD(SHIFT_CURSOR_RIGHT);
}


void HLCD_shiftDisplayRight(u8 n){
	for(; n > 0; n--)
		HLCD_writeCMD(SHIFT_DISPLAY_RIGHT);

}

void HLCD_shiftDisplayLeft(u8 n){
	for(; n > 0; n--)
		HLCD_writeCMD(SHIFT_DISPLAY_LEFT);
}

/**
 * Adds a custom character to the display memory.
 * To display that custom character pass indx of the character to writeData().
 * Input: 	indx	the index of the custom character. Range between 0 to 7. Used to display the character by passing it to writeData()
 * 			pattern array of 7 elements each element is an 8 bit pattern for each row of the character
 * */
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
	LDelay_ms(delay);
	MDIO_setPinValue(HLCD_CONTROL_PORT, HLCD_EN, LOW);
}


void numberToString(u64 i, u8 b[]){
    u8* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    u64 shifter = i;
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
