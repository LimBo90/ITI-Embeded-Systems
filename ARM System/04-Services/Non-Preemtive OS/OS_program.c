#include "LSTD_TYPES.h"

#include "OS_private.h"
#include "OS_config.h"
#include "OS_interface.h"
#include "MSTK_interface.h"

Task sysTasks[N_TASKS] = {0};


/**
 * Initializes OS
 */
void OS_voidInit(){
	MSTK_voidInit();
	MSTK_voidSetLoadValue(500000);
	MSTK_voidSetCallback(OS_voidScheduler);
}

/**
 * Starts OS
 */
void OS_voidStart(){
	MSTK_voidStart();
}

/**
 * Creates a task within the OS that's called periodically.
 */
u8 OS_voidCreateTask(void (*func) (void), u32 period, u32 priority, u32 firstDelay, u8 initialState ){
	u8 status = SUCCESS;
	if(priority < N_TASKS)
	{
		if(sysTasks[priority].periodicity == 0){
			sysTasks[priority].periodicity = period;
			sysTasks[priority].taskHandler = func;
			sysTasks[priority].state = initialState;
			sysTasks[priority].firstDelay = firstDelay;
		}else{
			status = ERR_OVERWRITE_ATTEMP;
		}
	}else{
		status = ERR_NOT_VALID_PRIORITY;
	}
	return status;
}


/**
 * Deletes task from queue.
 * Returns either SUCESS, ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidDeleteTask(u32 priority){
	u8 status = SUCCESS;
	if(priority < N_TASKS){
		sysTasks[priority].periodicity = 0;
	}else{
		status = ERR_NOT_VALID_PRIORITY;
	}
	return status;
}

/**
 * Resumes a task
 * Returns either SUCESS or ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidResume(u32 priority){
	u8 status = SUCCESS;
	if(priority < N_TASKS){
		sysTasks[priority].state = TASK_STATE_READY;
	}else{
		status = ERR_NOT_VALID_PRIORITY;
	}
	return status;
}

/**
 * Suspends a task
 * Returns either SUCESS or ERR_NOT_VALID_PRIORITY
 */
u8 OS_voidSuspend(u32 priority){
	u8 status = SUCCESS;
	if(priority < N_TASKS){
		sysTasks[priority].state = TASK_STATE_SUSPENDED;
	}else{
		status = ERR_NOT_VALID_PRIORITY;
	}
	return status;
}


/**
 * Scheduler for the OS
 * Responsible for deciding which task to currently run and which task to halt
 */
void OS_voidScheduler(){
	u32 i = 0;
	for(i = 0; i < N_TASKS; i++){
		if(sysTasks[i].periodicity != 0){
			if(sysTasks[i].state == TASK_STATE_READY){
				sysTasks[i].firstDelay--;
				if(sysTasks[i].firstDelay == 0){
					sysTasks[i].taskHandler();
					sysTasks[i].firstDelay = sysTasks[i].periodicity;
				}
			}
		}
	}
}

