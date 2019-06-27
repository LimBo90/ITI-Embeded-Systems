#ifndef HSERVO_INTERFACE_H
#define HSERVO_INTERFACE_H


/* Servo motor connections */
/* BLACK wire ---> GND */
/* RED wire ---> Vcc */
/* ORANGE wire ---> OC1A */
/* servo produces PWM signal using timer 1 mode 14 so MTIMER_config.h has to be configured  */

void HServo_init(void);
void HServo_rotate(u8 angle);



#endif
