#ifndef _MUART_CONFIG_H
#define _MUART_CONFIG_H_

#include "MUART_private.h"

#define F_OSC 				8000000
#define MUART_MODE			MUART_MODE_ASYNCH_NORMAL_SPEED
#define MUART_DATA_SIZE		MUART_DATA_SIZE_8
#define MUART_STOP_BITS		MUART_ONE_STOP_BITS
#define MUART_PARITY		MUART_PARITY_DISABLE
#define MUART_BAUD_RATE		250000ULL

#endif
