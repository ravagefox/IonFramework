#ifndef __TASK_C__
#define __TASK_C__

#include "../../Kernel/Threading/task.h"

void toggleTaskState(Task* task, int state) {
	if ((task->state & state)) {
		task->state &= ~state;
	}
	else {
		task->state |= state;
	}
}

void pauseTask(Task* task) {
	if ((task->state & TASK_STATE_PAUSE)) { return; }
	task->state |= TASK_STATE_PAUSE;
}
void resumeTask(Task* task) {
	if (!(task->state & TASK_STATE_PAUSE)) { return; }
	task->state &= ~TASK_STATE_PAUSE;
}

void startTask(Task* task) {
	if ((task->state & TASK_STATE_IDLE)) { return; }
	task->state |= TASK_STATE_IDLE;
}
void endTask(Task* task) {
	if ((task->state & TASK_STATE_ENDREQ)) { return; }
	task->state |= TASK_STATE_ENDREQ;
}

void setLongrunningTaskState(Task* task) {
	if ((task->state & TASK_STATE_LONGRUN)) { return; }
	task->state |= TASK_STATE_LONGRUN;
}

void freeTask(Task* task) {

	// free(task->function);
	// free(task->init);
	free(task);

	task = nullptr;
}

void createTask(Task* task, int (*function)(struct Task*), unsigned long interval) {
	*task = (Task*)malloc(sizeof(Task));

	if (!task) {
		freeTask(task);
		return;
	}

	*(task)->interval = interval > 0 ? interval : 1000;
	*(task)->function = function;
	*(task)->init = nullptr;
	*(task)->last_execution = 0;
	*(task)->state = TASK_STATE_IDLE;
	*(task)->priority = TASK_PRIORITY_MED;

}


bool checkTaskState(Task* task) {
	if (!task->function || task->function == nullptr) {
		setTaskState(task, TASK_STATE_ERR);
		return false;
	}

	if ((task->state & TASK_STATE_ENDREQ)) {
		freeTask(task);
		return false;
	}

	if ((task->state & TASK_STATE_IDLE)) {
		return false;
	}

	return true;
}


bool executeTask(
	Task* task,
	const unsigned long environmentTicks) {

	int lastError = 0;
	if (environmentTicks - task->last_execution < task->interval) {
		return false;
	}

	if (!checkTaskState(task)) { return false; }

	if (!(task->state & TASK_STATE_PAUSE)) {
		lastError = task->function(task);
	}

	task->last_execution = environmentTicks;
	return true;
}

#endif

