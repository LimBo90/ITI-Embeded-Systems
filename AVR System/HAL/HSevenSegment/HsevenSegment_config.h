#ifndef HSEVENSEGMENT_CONFIG_H
#define HSEVENSEGMENT_CONFIG_H


/**
 * Number of seven segments in the system
 */
#define HSEVENSEGMENT_ONE_SEVEN_SEGMENT		0
#define HSEVENSEGMENT_TWO_SEVEN_SEGMENTS	1
#define HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS	HSEVENSEGMENT_ONE_SEVEN_SEGMENT

/**
 * which ports the seven segment is connected to
*
*   The connection to each port will be
*   MCU port        7 segment pins
*   PIN0  -----------> a
*   PIN1  -----------> b
*   PIN2  -----------> c
*   PIN3  -----------> d
*   PIN4  -----------> e
*   PIN5  -----------> f
*   PIN6  -----------> g
*   PIN7  -----------> COM
*/
#define HSEVENSEGMENT_ONES_PORT	PORTC

#if HSEVENSEGMENT_CFG_NO_SEVEN_SEGMENTS == HSEVENSEGMENT_TWO_SEVEN_SEGMENTS
#define HSEVENSEGMENT_TENS_PORT	PORTB
#endif



#endif
