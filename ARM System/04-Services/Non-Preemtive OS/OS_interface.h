#ifndef _OS_INTERFACE_H_
#define _OS_INTERFACE_H_

#define TASK_STATE_SUSPENDED 0
#define TASK_STATE_READY	 1

#define SUCCESS						0
#define ERR_NOT_VALID_PRIORITY		1	//when passing a not valid priority
#define	ERR_OVERWRITE_ATTEMP		2	//when trying to overwrite a function

/**
 * Initializes OS
 */
void OS_voidInit();

/**
 * Creates a task within the OS that's called periodicaly.
 * Returns either SUCCESS,  ERR_OVERWRITE_ATTEMP or ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidCreateTask(void (*func) (void), u32 period, u32 priority, u32 firstDelay, u8 initialState);


/**
 * Deletes task from queue.
 * Returns either SUCESS, ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidDeleteTask(u32 priority);


/**
 * Resumes a task
 * Returns either SUCESS or ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidResume(u32 priority);


/**
 * Suspends a task
 * Returns either SUCESS or ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidSuspend(u32 priority);


/**
 * Starts OS
 */
void OS_voidStart();

#endif
