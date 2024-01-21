#ifndef __TASK_SCHEDULER__
#define __TASK_SCHEDULER__

#include "../priorityQueue.h"


typedef struct {
	PriorityQueue* queue;

} TaskScheduler;



void initTaskScheduler(TaskScheduler* scheduler);
void runScheduler(TaskScheduler* scheduler, const unsigned long environmentTicks);
void freeScheduler(TaskScheduler* scheduler);



#endif

