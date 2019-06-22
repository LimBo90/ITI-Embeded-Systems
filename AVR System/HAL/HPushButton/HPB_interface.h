#ifndef HPB_INTERFACE_H
#define HPB_INTERFACE_H


typedef enum {
    HPB_Released,
    HPB_Pressed,
	HPB_Bouncing
} HPB_State;

/****** Configurations *******/
#define HPB_CONNECTION_PULLUP	1
#define HPB_CONNECTION_PULLDOWN	0
/**
 * Initalizes push button
 */
void HPB_init(void);

/**
 * Returns the state of the push button
 */
HPB_State HPB_getState(u8 Copy_u8ButtonIndx);


#endif
