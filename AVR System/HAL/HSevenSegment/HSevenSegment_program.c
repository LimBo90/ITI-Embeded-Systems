#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "HSevenSegment_interface.h"


/*
*   initalizes the port connected to the 7 segment display
*   The connection will be
*   MCU port        7 segment pins
*   PIN0  -----------> a
*   PIN1  -----------> b
*   PIN2  -----------> c
*   PIN3  -----------> d
*   PIN4  -----------> e
*   PIN5  -----------> f
*   PIN6  -----------> g
*   PIN7  -----------> vcc
*/

void HSevenSegment_init(u8 port){
    MDIO_setPortDirection(port, 0xFF, OUTPUT);
    MDIO_setPortToValue(port, 255);
}

/*
 * Display a number from 0 to 9 to the seven segment display connected to port
 * input:	port: the port connected to the seven segment (PORTA, PORTB, PORTC or PORTD)
 */

void HSevenSegment_displayNum(u8 port, u8 num){
    switch(num){
        case 0: MDIO_setPortToValue(port, 0xFF, ZERO);    return;
        case 1: MDIO_setPortToValue(port, 0xFF,  ONE);    return;
        case 2: MDIO_setPortToValue(port, 0xFF,  TWO);    return;
        case 3: MDIO_setPortToValue(port, 0xFF,  THREE);    return;
        case 4: MDIO_setPortToValue(port, 0xFF,  FOUR);    return;
        case 5: MDIO_setPortToValue(port, 0xFF,  FIVE);    return;
        case 6: MDIO_setPortToValue(port, 0xFF,  SIX);    return;
        case 7: MDIO_setPortToValue(port, 0xFF,  SEVEN);    return;
        case 8: MDIO_setPortToValue(port, 0xFF,  EIGHT);    return;
        case 9: MDIO_setPortToValue(port, 0xFF,  NINE);    return;
        default:
        	MDIO_setPortToValue(port, 0xFF,  ERROR);    return;

    }
    return;
}
