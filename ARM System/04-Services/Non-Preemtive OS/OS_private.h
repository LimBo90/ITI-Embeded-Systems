#ifndef _OS_PRIVATE_H_
#define _OS_PRIVATE_H_

typedef struct{
	u8 state;
	void (*taskHandler) (void);
	u32 periodicity;
	u32 firstDelay;
}Task;


void OS_voidScheduler();

#endif
