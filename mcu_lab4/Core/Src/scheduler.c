/*
 * scheduler.c
 *
 *  Created on: Nov 28, 2022
 *      Author: nguye
 */

#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
int Error_code_G = 0;

void SCH_Init() {
	for (int i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}

	Error_code_G = 0;
	//Timer_init();
	//Watchdog_init();
}

void Shift_Task_To_Left(int index_a, int index_b) {
	SCH_tasks_G[index_a].pTask = SCH_tasks_G[index_b].pTask;
	SCH_tasks_G[index_a].Delay = SCH_tasks_G[index_b].Delay;
	SCH_tasks_G[index_a].Period =  SCH_tasks_G[index_b].Period;
	SCH_tasks_G[index_a].RunMe = SCH_tasks_G[index_b].RunMe;

	SCH_tasks_G[index_a].TaskID = SCH_tasks_G[index_b].TaskID;
}
void SCH_Add_Task ( void (*pFunction)() , uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){

		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period =  PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Dispatch_Tasks(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
			// If it's one-shot task, remove it form the array
			if (SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
			}
		}
	}

	// Report system status
	SCH_Report_Status();
	// The scheduler enters idle mode at this point
	//SCH_Go_To_Sleep();
}

void SCH_Update(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].Delay > 0) SCH_tasks_G[i].Delay--;
		else {
			 SCH_tasks_G[i].Delay =  SCH_tasks_G[i].Period;
			 SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Delete_Task(uint16_t TASK_INDEX) {
	if (TASK_INDEX < 0 || TASK_INDEX > current_index_task) return;
	// Shift task from TASK_INDEX + 1 to the left
	for (int i = TASK_INDEX; i < current_index_task; i++) {
		Shift_Task_To_Left(i, i + 1);
	}
	// Remove last index task
	SCH_tasks_G[current_index_task].pTask = 0x0000 ;
	SCH_tasks_G[current_index_task].Delay = 0;
	SCH_tasks_G[current_index_task].Period = 0;
	SCH_tasks_G[current_index_task].RunMe = 0;
	current_index_task--;
}

void SCH_Report_Status(void) {
#ifdef SCH_REPORT_ERRORS
	// ONLY APPLIES IF WE ARE REPORTING ERRORS
	// Check for a new  error code
	if (Error_code_G != Last_error_code_G) {
		// Negative logic on LEDs assumed
		Error_port = 255 - Error_code_G;
		Last_error_code_G = Error_code_G;

		if (Error_code_G != 0) {
			Error_tick_count_G = 60000;
		} else {
			Error_tick_count_G = 0;
		}
	} else {
		if (Error_tick_count_G != 0) {
			if (--Error_tick_count_G == 0) {
				Error_code_G = 0; // Reset error code
			}
		}
	}
#endif
}
