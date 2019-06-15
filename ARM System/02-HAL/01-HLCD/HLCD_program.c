#include "LUTILS.h"
#include "LSTD_TYPES.h"

#include "MDIO_interface.h"
#include "HLCD_config.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"

static void HLocal_voidLatchEnPin(u8 delay);
static void HLocal_voidNumberToString(s32 i, u8 b[]);

void HLCD_voidInit(){
    LUTILS_voidDelay_ms(30);
	//Sets control pins and data port pins to be output

	if(HLCD_U8_MODE_8BIT)
	    MDIO_voidSetPortMode(HLCD_DATA_PORT, 0x00FF, MDIO_MODE_OUTPUT_PUSHPULL_2);
	else
	    MDIO_voidSetPortMode(HLCD_DATA_PORT, 0x00F0, MDIO_MODE_OUTPUT_PUSHPULL_2);


    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_RS, MDIO_MODE_OUTPUT_PUSHPULL_2);
    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_RW, MDIO_MODE_OUTPUT_PUSHPULL_2);
    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_EN, MDIO_MODE_OUTPUT_PUSHPULL_2);
    LUTILS_voidDelay_ms(1);

    //Function set
	//sets the data length to 8bit or 4bit mode
	//sets the lcd to be 2 line display
	//sets the font to be 5 x 10 dots
	if(HLCD_U8_MODE_8BIT){
		HLCD_voidWriteCMD(FNSET_DATA_LENGTH_8_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	}else{
		//writes the upper 4 bits of command to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xF0, 0x20);
		HLocal_voidLatchEnPin(2);
		HLCD_voidWriteCMD(FNSET_DATA_LENGTH_4_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
	}
    LUTILS_voidDelay_ms(1);

    //Display ON/OFF Control
	//sets the display to be ON
	//display the cursor
	//makes the cursor blink
	HLCD_voidWriteCMD(DISPLAYCONTROL_DISPLAY_ON | DISPLAYCONTROL_CURSOR_ON | DISPLAYCONTROL_CURSOR_BLINK_ON);
	LUTILS_voidDelay_ms(1);

    //Clear Display
	HLCD_voidWriteCMD(CLEAR_DISPLAY);
	LUTILS_voidDelay_ms(2);

    //sets the move direction of cursor and display
	//sets the cursor to move to the right when a new character is displayed and the new character is added to the left (left to right)
	//sets the display to shift
	HLCD_voidWriteCMD(ENTRYMODE_LEFT_TO_RIGHT | ENTRYMODE_DISPLAY_SHIFT_OFF);
}

/**
 * Sends a command to the display
 */
void HLCD_voidWriteCMD(u8 cmd){
	//sets RS = LOW to write in the command register
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_RS, DIO_U8_LOW);
	//sets RW = LOW to write
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_RW, DIO_U8_LOW);
	//sets EN = LOW preparing for the latch
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_LOW);

    //writes the command to the data port
	if(HLCD_U8_MODE_8BIT){
		//writes the command to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xFF, cmd);
		HLocal_voidLatchEnPin(2);
	}else{
		//writes the upper 4 bits of command to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xF0, cmd);
		HLocal_voidLatchEnPin(2);

		//writes the lower 4 bits command to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xF0, cmd<<4);
		HLocal_voidLatchEnPin(2);
	}
	return;
}

void HLCD_voidWriteData(u8 data){
	//sets RS = HIGH to write in the data register
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_RS, DIO_U8_HIGH);
	//sets RW = LOW to write
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_RW, DIO_U8_LOW);
	//sets EN = LOW preparing for the latch
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_LOW);

    //writes the command to the data port
	if(HLCD_U8_MODE_8BIT){
		//writes the command to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xFF, data);
		HLocal_voidLatchEnPin(2);
	}else{
		//writes the upper 4 bits of data to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xF0, data);
		HLocal_voidLatchEnPin(2);

		//writes the lower 4 bits of data to the data port
		MDIO_voidSetPortValue(HLCD_DATA_PORT, 0xF0, data<<4);
		HLocal_voidLatchEnPin(2);
	}
	return;
}

/**
 * Displays a string
 */
void HLCD_voidWriteStr(u8 str[]){
	u8 i = 0;
	while(str[i] != '\0'){
		HLCD_voidWriteData(str[i]);
		i++;
	}
}

void HLCD_voidWriteNumber(u32 n){
	u8 buffer[16];
	HLocal_voidNumberToString(n, buffer);
	HLCD_voidWriteStr(buffer);
}



void HLCD_voidSetCursor(u8 row, u8 col){
	//The ranges are from 0 to 1 on the y-axis and from 0 to 15 on the x-axis
	if(!(row <= 1 && row >= 0 && col >= 0 && col <= 15))
		return;
	switch(row){
	case 0:
		//first line
		HLCD_voidWriteCMD(col| DDRAM_FIRST_LINE_START_ADDRESS);
		break;
	case 1:
		//second line
		HLCD_voidWriteCMD(col | DDRAM_SECOND_LINE_START_ADDRESS);
		break;
	}
	return;
}

/**
 * Adds a custom character to the display memory.
 * To display that custom character pass indx of the character to writeData().
 * Input: 	indx	the index of the custom character. Range between 0 to 7. Used to display the character by passing it to writeData()
 * 			pattern array of 7 elements each element is an 8 bit pattern for each row of the character. Because each row is 5 bits long the highest 3 bits of each row are ignored
 * */
void HLCD_voidAddCustomCharacter(u8 indx, u8 pattern[7]){
	//only 8 custom characters can be written from indx 0 to 7
	if(indx < 0 || indx > 7)
		return;

	//set address counter to CGRAM address
	u8 cgramAddress = indx * 8;
	HLCD_voidWriteCMD(SET_CGRAM_ADDRESS_CMD | cgramAddress);
	for(int i = 0; i < 7; i++){
		HLCD_voidWriteData(pattern[i]);
	}
	//the 8th row must be all zeroes
	HLCD_voidWriteData(0);
	//sets the address counter back to ddram
	HLCD_voidWriteCMD(DDRAM_FIRST_LINE_START_ADDRESS);
}

void HLCD_voidWriteCustomCharacter(u8 indx){
	HLCD_voidWriteData(indx);
}

void HLCD_voidShiftCursorLeft(){
		HLCD_voidWriteCMD(SHIFT_CURSOR_LEFT);
}

void HLCD_voidShiftCursorRight(){
		HLCD_voidWriteCMD(SHIFT_CURSOR_RIGHT);
}

void HLCD_voidShiftDisplayLeft(){
	HLCD_voidWriteCMD(SHIFT_DISPLAY_LEFT);
}

void HLCD_voidShiftDisplayRight(){
	HLCD_voidWriteCMD(SHIFT_DISPLAY_RIGHT);
}

void HLCD_voidClearDisplay(){
	HLCD_voidWriteCMD(CLEAR_DISPLAY);
}


static void HLocal_voidLatchEnPin(u8 delay){
	//latches the EN pin
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_HIGH);
	LUTILS_voidDelay_ms(delay);
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_LOW);
}


static void HLocal_voidNumberToString(s32 i, u8 b[]){
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    u32 shifter = i;
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



