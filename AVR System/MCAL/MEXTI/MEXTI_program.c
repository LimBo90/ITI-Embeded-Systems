
#include "LUTILS.h"
#include "LSTD_TYPES.h"

#include "MEXTI_interface.h"
#include "MEXTI_private.h"

void (*INT0_ISR_ptr) (void);
void (*INT1_ISR_ptr) (void);
void (*INT2_ISR_ptr) (void);

void __vector_1(void) __attribute__ ((signal, INTR_ATTRS));
void __vector_2(void) __attribute__ ((signal, INTR_ATTRS));
void __vector_3(void) __attribute__ ((signal, INTR_ATTRS));

void MEXTI_enableINT(u8 INT_no, u8 mode){
	SET_BIT(MEXTI_GICR, INT_no);
	switch(INT_no){
		case MEXTI_INT0: 
			switch(mode){
				case MEXTI_MODE_LOW_LEVEL:
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC00);
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC01);
					return;
				case MEXTI_MODE_LOGICAL_CHANGE:
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC00);
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC01);
					return;
				case MEXTI_MODE_FALLING_EDGE:
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC00);
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC01);
					return;
				case MEXTI_MODE_RISING_EDGE:
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC00);
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC01);
					return;
			}
			break;
		case MEXTI_INT1: 
			switch(mode){
				case MEXTI_MODE_LOW_LEVEL:
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC10);
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC11);
					return;
				case MEXTI_MODE_LOGICAL_CHANGE:
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC10);
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC11);
					return;
				case MEXTI_MODE_FALLING_EDGE:
					CLR_BIT(MEXTI_MCUCR, MEXTI_ISC10);
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC11);
					return;
				case MEXTI_MODE_RISING_EDGE:
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC10);
					SET_BIT(MEXTI_MCUCR, MEXTI_ISC11);
					return;
			}
			break;
		case MEXTI_INT2:
			switch(mode){
				case MEXTI_MODE_FALLING_EDGE:
					CLR_BIT(MEXTI_MCUCSR, MEXTI_ISC2);
					return;
				case MEXTI_MODE_RISING_EDGE:
					SET_BIT(MEXTI_MCUCSR, MEXTI_ISC2);
					return;
				}
	}
	return;
}


void MEXTI_disableINT(u8 INT_no){
	CLR_BIT(MEXTI_GICR, INT_no);
}

u8 MEXTI_checkINT(u8 INT_no){
	return GET_BIT(MEXTI_GIFR, INT_no);
}

void MEXTI_registerISR(u8 INT_no, void (*isr_func)(void)){
	switch(INT_no){
	case MEXTI_INT0:	INT0_ISR_ptr = isr_func;	return;
	case MEXTI_INT1:	INT1_ISR_ptr = isr_func;	return;
	case MEXTI_INT2:	INT2_ISR_ptr = isr_func;	return;
	}
}

void MEXTI_enableInterrupts(){
	SET_BIT(MEXTI_SREG, MEXTI_I);
}

void MEXTI_disableInterrupts(){
	CLR_BIT(MEXTI_SREG, MEXTI_I);
}

void __vector_1(void){
	INT0_ISR_ptr();
}

void __vector_2(void){
	INT1_ISR_ptr();
}

void __vector_3(void){
	INT2_ISR_ptr();
}


