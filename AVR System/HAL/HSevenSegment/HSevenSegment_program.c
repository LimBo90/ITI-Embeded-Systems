#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "HSevenSegment_private.h"
#include "HsevenSegment_config.h"
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

void HSevenSegment_init(){

#if HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS == HSEVENSEGMENT_ONE_SEVEN_SEGMENT
    MDIO_setPortDirection(HSEVENSEGMENT_ONES_PORT, 0xFF, OUTPUT);
    MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT,0xFF, 0x00);
#elif HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS == HSEVENSEGMENT_TWO_SEVEN_SEGMENTS
    MDIO_setPortDirection(HSEVENSEGMENT_ONES_PORT, 0xFF, OUTPUT);
    MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT,0xFF, 0xFF);
    MDIO_setPortDirection(HSEVENSEGMENT_TENS_PORT, 0xFF, OUTPUT);
    MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT,0xFF, 0xFF);
#else
#error "HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS configured incorrectly in HSEVENSEGMENT_config.h"
#endif
}

/*
 * Display a number from 0 to 9 to the seven segment display connected to port
 * input:	port: the port connected to the seven segment (PORTA, PORTB, PORTC or PORTD)
 */

void HSevenSegment_displayNum(u8 num){
	u8 ones = num % 10;

#if HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS == HSEVENSEGMENT_TWO_SEVEN_SEGMENTS
	u8 tens = (num / 10) % 10;
#endif

    switch(ones){
        case 0: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF, ZERO);		break;
        case 1: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  ONE);		break;
        case 2: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  TWO);		break;
        case 3: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  THREE);		break;
        case 4: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  FOUR);		break;
        case 5: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  FIVE);		break;
        case 6: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  SIX);    	break;
        case 7: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  SEVEN);		break;
        case 8: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  EIGHT);		break;
        case 9: MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  NINE);		break;
        default:
        	MDIO_setPortToValue(HSEVENSEGMENT_ONES_PORT, 0xFF,  ERROR);			break;
    }

#if HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS == HSEVENSEGMENT_TWO_SEVEN_SEGMENTS
    switch(tens){
        case 0: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF, ZERO);		break;
        case 1: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  ONE);		break;
        case 2: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  TWO);		break;
        case 3: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  THREE);		break;
        case 4: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  FOUR);		break;
        case 5: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  FIVE);		break;
        case 6: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  SIX);		break;
        case 7: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  SEVEN);		break;
        case 8: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  EIGHT);		break;
        case 9: MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  NINE);		break;
        default:
        	MDIO_setPortToValue(HSEVENSEGMENT_TENS_PORT, 0xFF,  ERROR);			break;
    }
#endif
    return;

}
