#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "HKPD_interface.h"

u8 KEYPAD[4][4] = {{'1', '2', '3', 'A'},
                   {'4', '5', '6', 'B'},
                   {'7', '8', '9', 'C'},
                    {'#', '0', '*', 'K'}};

void HKPD_init(void){
    //sets C1,C2,c3,C4 as ouput pins
    MDIO_setPortDirection(HKPD_PORT, 0x0F, OUTPUT);
    //sets R1,R2,R3,R4 as input pins with pull up
    MDIO_setPortDirection(HKPD_PORT, 0xF0, INPUT_PULLUP);

    //outputs HIGH on pins C1, C2, C3, C4
    MDIO_setPort(HKPD_PORT, 0x0F);
    return;
}

u8 HKPD_getKey(){
    MDIO_setPort(HKPD_PORT, 0x0F);
    for(u8 i = 3; i >= 0; i--){
        MDIO_setPinValue(HKPD_PORT, i, LOW);
        for(u8 j = 4; j <= 7; j++){
            if(MDIO_getPinValue(HKPD_PORT, j) == LOW){
                while(MDIO_getPinValue(HKPD_PORT, j) == LOW) ;
                MDIO_setPinValue(HKPD_PORT, i, HIGH);
                return KEYPAD[j-4][3-i];
            }
        }
        MDIO_setPinValue(HKPD_PORT, i, HIGH);
    }
    return HKPD_NULL_CHARACTER;
}


