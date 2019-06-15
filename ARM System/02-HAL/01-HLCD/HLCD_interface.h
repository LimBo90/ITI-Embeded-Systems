#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H




void HLCD_voidInit(void);
void HLCD_voidWriteCMD(u8 cmd);
void HLCD_voidWriteData(u8 data);
void HLCD_voidWriteStr(u8 str[]);
void HLCD_voidWriteNumber(u32 n);
void HLCD_voidSetCursor(u8 row, u8 col);
void HLCD_voidAddCustomCharacter(u8 indx, u8 pattern[7]);
void HLCD_voidWriteCustomCharacter(u8 indx);
void HLCD_voidClearDisplay();
void HLCD_voidShiftCursorLeft();
void HLCD_voidShiftCursorRight();
void HLCD_voidShiftDisplayLeft();
void HLCD_voidShiftDisplayRight();


#endif
