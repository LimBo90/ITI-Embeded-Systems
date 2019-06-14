#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

/****** Configurations *******/
#define HLCD_MODE_8_BIT 0
#define HLCD_MODE_4_BIT 1


#define HLCD_CURSOR_ON 0b00001010
#define HLCD_CURSOR_OFF 0b00001000
#define HLCD_CURSOR_BLINK_ON 0b00001001
#define HLCD_CURSOR_BLINK_OFF 0b00001000

#define HLCD_LEFT 0
#define HLCD_RIGHT 1
/**
 * Initalizes LCD
 */
void HLCD_init(void);

/**
 * Sends a command to LCD
 */
void HLCD_writeCMD(u8 cmd);

/**
 * Displays A character to the LCD
 */
void HLCD_writeData(u8 data);

/**
 * Displays a string on the LCD
 */
void HLCD_writeStr(u8 str[]);

/**
 * Displays a number on the LCD
 */
void HLCD_writeNumber(u16 n);

/**
 * changes the position of the cursor
 * The ranges are from 0 to 1 on the y-axis and from 0 to 15 on the x-axis
 */
void HLCD_setCursor(u8 x, u8 y);

/**
 * Clears the LCD
 */
void HLCD_clearDisplay();

/**
 * Moves the cursor to the right n times
 */
void HLCD_shiftCursorRight(u8 n);

/**
 * Moves the cursor to the left n times
 */
void HLCD_shiftCursorLeft(u8 n);

/**
 * Shifts the display to the left n times
 */
void HLCD_shiftDisplayRight(u8 n);

/**
 * Shifts the display to the left n times
 */
void HLCD_shiftDisplayLeft(u8 n);

/**
 * Adds a custom character to the display memory.
 * To display that custom character pass indx of the character to HLCD_displayCustomCharacter().
 * Input: 	indx	the index of the custom character. Range between 0 to 7. Used to display the character by passing it to writeData()
 * 			pattern array of 7 elements each element is an 8 bit pattern for each row of the character
 * */
void HLCD_addCustomCharacter(u8 indx, u8 pattern[7]);

/**
 * Displays A custom character that's been added.
 * Input: indx the index of the custom character. the same index used when adding the custom character
 */
void HLCD_displayCustomCharacter(u8 indx);

#endif
