#include "LUTILS.h"
#include "LSTD_TYPES.h"

#include "MDIO_interface.h"
#include "HLCD_config.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"

static void HLocal_voidDelay_ms(u16 value);
static void HLocal_voidLatchEnPin(u8 delay);
static void HLocal_voidNumberToString(s32 i, u8 b[]);

void HLCD_voidInit(){
    HLocal_voidDelay_ms(30);
	//Sets control pins and data port pins to be output
    MDIO_voidSetPortMode(HLCD_DATA_PORT, 0x00FF, MDIO_MODE_OUTPUT_PUSHPULL_2);
    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_RS, MDIO_MODE_OUTPUT_PUSHPULL_2);
    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_RW, MDIO_MODE_OUTPUT_PUSHPULL_2);
    MDIO_voidSetPinMode(HLCD_CONTROL_PORT, HLCD_EN, MDIO_MODE_OUTPUT_PUSHPULL_2);
    HLocal_voidDelay_ms(1);

    //Function set
	//sets the data length to 8bit or 4bit mode
	//sets the lcd to be 2 line display
	//sets the font to be 5 x 10 dots
    HLCD_voidWriteCMD(FNSET_DATA_LENGTH_8_BIT| FNSET_TWO_LINE_DISPLAY | FNSET_FONT_5x7);
    HLocal_voidDelay_ms(1);

    //Display ON/OFF Control
	//sets the display to be ON
	//display the cursor
	//makes the cursor blink
	HLCD_voidWriteCMD(DISPLAYCONTROL_DISPLAY_ON | DISPLAYCONTROL_CURSOR_ON | DISPLAYCONTROL_CURSOR_BLINK_ON);
	HLocal_voidDelay_ms(1);

    //Clear Display
	HLCD_voidWriteCMD(CLEAR_DISPLAY);
	HLocal_voidDelay_ms(2);

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
	MDIO_voidSetPortValue(HLCD_DATA_PORT, 0x00FF, cmd);
    HLocal_voidLatchEnPin(2);

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
    MDIO_voidSetPortValue(HLCD_DATA_PORT, 0x00FF, data);
    HLocal_voidLatchEnPin(2);

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

void HLCD_voidWriteNumber(u16 n){
	u8 buffer[16];
	HLocal_voidNumberToString(n, buffer);
	HLCD_voidWriteStr(buffer);
}

void HLCD_voidClearDisplay(){
	HLCD_voidWriteCMD(CLEAR_DISPLAY);
}

static void HLocal_voidLatchEnPin(u8 delay){
	//latches the EN pin
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_HIGH);
	HLocal_voidDelay_ms(delay);
	MDIO_voidSetPinValue(HLCD_CONTROL_PORT, HLCD_EN, DIO_U8_LOW);
}


static void HLocal_voidDelay_ms(u16 value){
	u32 i;
	for(i=2666*value; i > 0; i--)
		asm("NOP");
	return;
}

void HLocal_voidNumberToString(s32 i, u8 b[]){
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



