#ifndef HSERVO_INTERFACE_H
#define HSERVO_INTERFACE_H

#include "LUTILS.h"
#include "LSTD_TYPES.h"
#include "HServo_private.h"

/* Servo motor connections */
/* BLACK wire ---> GND */
/* RED wire ---> Vcc */
/* ORANGE wire ---> OC1A */

void HServo_init(void);
void HServo_rotate(u8 angle);



#endif
