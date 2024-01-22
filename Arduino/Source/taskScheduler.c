#ifndef __TASK_SCHEDULER_C_
#define __TASK_SCHEDULER_C_


#include "../Kernel/Threading/taskScheduler.h"

void initTaskScheduler(TaskScheduler* scheduler) {

	PriorityQueue* queue;
	initPriorityQueue(queue);

	if (!scheduler) {
		*scheduler = (TaskScheduler*)malloc(sizeof(TaskScheduler));
		*(scheduler)->queue = queue;
		return;
	}

	scheduler->queue = queue;
}

void runScheduler(TaskScheduler* scheduler, const unsigned long environmentTicks) {
	if (isEmpty(scheduler->queue)) { return; }

	Task* task = dequeue(scheduler->queue);

	if (task->init && !task->doneInit) {
		task->init();
		task->doneInit = true;
	}

	bool executionState = executeTask(task, environmentTicks);
	task->last_execution = environmentTicks;

	if (!(task->state & TASK_STATE_LONGRUN)) {
		if ((task->state & TASK_STATE_PAUSE)) {
			enqueue(scheduler->queue, task);
			return;
		}
		else if ((task->state & TASK_STATE_IDLE)) {
			startTask(task);
			enqueue(scheduler->queue, task);
			return;
		}
		else {
			freeTask(task);
			return;
		}
	}

	enqueue(scheduler->queue, task);
}

void freeScheduler(TaskScheduler* scheduler) {
	bool canClear = true;
	for (int i = 0; i < MAX_TASKS_IN_QUEUE; i++) {
		Task* task = getTaskAtIndex(scheduler->queue, i);
		if (task & (task->state & TASK_STATE_WAITING)) {
			canClear = false;
			break;
		}
	}

	if (!canClear) { return; }

	while (!isEmpty(scheduler->queue)) {
		Task* task = dequeue(scheduler->queue);
		if (task) { freeTask(task); }
	}

	free(scheduler->queue->tasks);
	free(scheduler->queue);
	free(scheduler);
}
#endif

