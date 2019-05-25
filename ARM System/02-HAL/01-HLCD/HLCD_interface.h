#ifndef HLCD_INTERFACE_H
#define HLCD_INTERFACE_H

void HLCD_voidInit(void);
void HLCD_voidWriteCMD(u8 cmd);
void HLCD_voidWriteData(u8 data);
void HLCD_voidWriteStr(u8 str[]);
void HLCD_voidClearDisplay();
void HLCD_voidWriteNumber(u16 n);
#endif
