#include "LSTD_TYPES.h"
#include "LUTILS.h"
#include "MDIO_interface.h"
#include "MDIO_private.h"



void MDIO_setPinDirection(u8 port, u8 pin, u8 direction){
	switch(direction){
	case INPUT:
		switch(port){
		case PORTA:	CLR_BIT(MDIO_DDRA, pin);	break;
		case PORTB: CLR_BIT(MDIO_DDRB, pin);	break;
		case PORTC:	CLR_BIT(MDIO_DDRC, pin);	break;
		case PORTD:	CLR_BIT(MDIO_DDRD, pin);	break;
		}break;
	case OUTPUT:
		switch(port){
		case PORTA:	SET_BIT(MDIO_DDRA, pin);	break;
		case PORTB:	SET_BIT(MDIO_DDRB, pin);	break;
		case PORTC:	SET_BIT(MDIO_DDRC, pin);	break;
		case PORTD:	SET_BIT(MDIO_DDRD, pin);	break;
		}break;
	case INPUT_PULLUP:
		switch(port){
		case PORTA:
			CLR_BIT(MDIO_DDRA, pin);
			SET_BIT(MDIO_PORTA, pin);
			break;
		case PORTB:
			CLR_BIT(MDIO_DDRB, pin);
			SET_BIT(MDIO_PORTB, pin);
			break;
		case PORTC:
			CLR_BIT(MDIO_DDRC, pin);
			SET_BIT(MDIO_PORTC, pin);
			break;
		case PORTD:
			CLR_BIT(MDIO_DDRD, pin);
			SET_BIT(MDIO_PORTD, pin);
			break;
		}break;
		case INPUT_PULLDOWN:
			switch(port){
			case PORTA:
				CLR_BIT(MDIO_DDRA, pin);
				CLR_BIT(MDIO_PORTA, pin);
				break;
			case PORTB:
				CLR_BIT(MDIO_DDRB, pin);
				CLR_BIT(MDIO_PORTB, pin);
				break;
			case PORTC:
				CLR_BIT(MDIO_DDRC, pin);
				CLR_BIT(MDIO_PORTC, pin);
				break;
			case PORTD:
				CLR_BIT(MDIO_DDRD, pin);
				CLR_BIT(MDIO_PORTD, pin);
				break;
			}break;
	}
    return;
}

/**
 * Sets the pin value of an output pin to either HIGH or LOW
 * preconditions:	The pin will have to be configured as output pin using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			pin:		The pin number
 * 			value: 	Either HIGH or LOW
 */
void MDIO_setPinValue(u8 port, u8 pin, u8 value){
	switch(value){
	case HIGH:
		switch(port){
		case PORTA: 	SET_BIT(MDIO_PORTA, pin); break;
		case PORTB: 	SET_BIT(MDIO_PORTB, pin); break;
		case PORTC: 	SET_BIT(MDIO_PORTC, pin); break;
		case PORTD: 	SET_BIT(MDIO_PORTD, pin); break;
		}break;
	case LOW:
		switch(port){
		case PORTA: 	CLR_BIT(MDIO_PORTA, pin); break;
		case PORTB: 	CLR_BIT(MDIO_PORTB, pin); break;
		case PORTC: 	CLR_BIT(MDIO_PORTC, pin); break;
		case PORTD: 	CLR_BIT(MDIO_PORTD, pin); break;
		}break;
	}
	return;
}

/**
 * Returns the pin value of an input pin
 * preconditions:	The pin will have to be configured as input pin using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			pin:		The pin number
 * output: The value of the pin (HIGH or LOW)
 */
u8 MDIO_getPinValue(u8 port, u8 pin){
	switch(port){
			case PORTA: 	return GET_BIT(MDIO_PINA, pin);
			case PORTB: 	return GET_BIT(MDIO_PINB, pin);
			case PORTC: 	return GET_BIT(MDIO_PINC, pin);
			case PORTD: 	return GET_BIT(MDIO_PIND, pin);
			}
	return 0;
}

/**
 * Toggles an output pin (Sets to HIGH if it's LOW and set's to LOW if it's HIGH)
 * preconditions:	The pin will have to be configured as output pin using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			pin:		The pin number
 */
void MDIO_togglePin(u8 port, u8 pin){
	switch(port){
	case PORTA:	TOGGLE_BIT(MDIO_PORTA, pin);	return;
	case PORTB:	TOGGLE_BIT(MDIO_PORTB, pin);	return;
	case PORTC:	TOGGLE_BIT(MDIO_PORTC, pin);	return;
	case PORTD:	TOGGLE_BIT(MDIO_PORTD, pin);	return;
	}
}

/**
 * Sets the direction of specific output pins in port to be either input, output, input pull up or input pull down
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			mask:		The pins the direction of which will be set
 * 			direction: 	Either INPUT, OUTPUT, INPUT_PULLUP or INPUT_PULLDOWN
 */
void MDIO_setPortDirection(u8 port, u8 mask, u8 direction){
	switch(direction){
	case INPUT:
		switch(port){
		case PORTA:	MDIO_DDRA &= ~mask;	break;
		case PORTB:	MDIO_DDRB &= ~mask;	break;
		case PORTC:	MDIO_DDRC &= ~mask;	break;
		case PORTD:	MDIO_DDRD &= ~mask;	break;
		}
		break;
	case OUTPUT:
		switch(port){
		case PORTA:	MDIO_DDRA |= mask;	break;
		case PORTB:	MDIO_DDRB |= mask;	break;
		case PORTC:	MDIO_DDRC |= mask;	break;
		case PORTD:	MDIO_DDRD |= mask;	break;
		}
		break;
	case INPUT_PULLUP:
		switch(port){
				case PORTA:
					MDIO_DDRA &= ~mask;
					MDIO_PORTA |= mask;
					break;
				case PORTB:
					MDIO_DDRB &= ~mask;
					MDIO_PORTB |= mask;
					break;
				case PORTC:
					MDIO_DDRC &= ~mask;
					MDIO_PORTC |= mask;
					break;
				case PORTD:
					MDIO_DDRD &= ~mask;
					MDIO_PORTD |= mask;
					break;
				}
		break;
	case INPUT_PULLDOWN:
		switch(port){
				case PORTA:
					MDIO_DDRA &= ~mask;
					MDIO_PORTA &= ~mask;
					break;
				case PORTB:
					MDIO_DDRB &= ~mask;
					MDIO_PORTB &= ~mask;
					break;
				case PORTC:
					MDIO_DDRC &= ~mask;
					MDIO_PORTC &= ~mask;
					break;
				case PORTD:
					MDIO_DDRD &= ~mask;
					MDIO_PORTD &= ~mask;
					break;
				}
		break;
	}
	return;
}

/**
 * Sets specific output pins pins in port to HIGH
 * preconditions:	The pins will have to be configured as output pins using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			mask:		The pins the direction of which will be set
 */
void MDIO_setPort(u8 port, u8 mask){
	switch(port){
	case PORTA: MDIO_PORTA |= mask; return;
	case PORTB: MDIO_PORTB |= mask; return;
	case PORTC: MDIO_PORTC |= mask; return;
	case PORTD: MDIO_PORTD |= mask; return;
	}
	return;
}

/**
 * Sets specific output pins in port to LOW
 * preconditions:	The pins will have to be configured as output pins using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			mask:		The pins the direction of which will be set
 */
void MDIO_clrPort(u8 port, u8 mask){
	switch(port){
	case PORTA: MDIO_PORTA &= ~mask; return;
	case PORTB: MDIO_PORTB &= ~mask; return;
	case PORTC: MDIO_PORTC &= ~mask; return;
	case PORTD: MDIO_PORTD &= ~mask; return;
	}
	return;
}

/**
 * Sets all pins of the port to a certain value
 * preconditions:	All port pins have to be configured as output pins using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port: 		The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			value:		The pins the direction of which will be set
 */
void MDIO_setPortToValue(u8 port, u8 mask,u8 value){
	switch(port){
	case PORTA: MDIO_PORTA = (MDIO_PORTA & ~mask) | (value & mask); return;
	case PORTB: MDIO_PORTB = (MDIO_PORTB & ~mask) | (value & mask); return;
	case PORTC: MDIO_PORTC = (MDIO_PORTC & ~mask) | (value & mask); return;
	case PORTD: MDIO_PORTD = (MDIO_PORTD & ~mask) | (value & mask); return;
	}
	return;
}

/**
 * Returns the value of specific input pins of a port
 * preconditions:	The pins will have to be configured as input pins using MDIO_setPortDirection or MDIO_setPinDirection
 * input:	port:	The port of the pin (PORTA, PORTB, PORTC, PORTD)
 * 			mask:	The pins the direction of which will be set
 * output: Return the value of the pins specified by the mask
 */
u8 MDIO_getPortValue(u8 port, u8 mask){
	switch(port){
	case PORTA:	return MDIO_PINA & mask;
	case PORTB:	return MDIO_PINB & mask;
	case PORTC:	return MDIO_PINC & mask;
	case PORTD:	return MDIO_PIND & mask;
	}
	return 0;
}

