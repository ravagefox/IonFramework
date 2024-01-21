#ifndef __PRIORITY_QUEUE_C__
#define __PRIORITY_QUEUE_C__

#include "../Kernel/kernel.h"
#include "../Kernel/priorityQueue.h"
#include "../Kernel/Threading/task.h"


void initPriorityQueue(PriorityQueue* queue) {
	if (!queue) {
		*queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
		*(queue)->size = 0;
		return;
	}

	queue->size = 0;
}

bool isEmpty(PriorityQueue* queue) {
	return queue->size == 0;
}
bool enqueue(PriorityQueue* queue, Task* task) {
	if (queue->size == MAX_TASK_COUNT) { return false; }

	int i = queue->size;
	while (i > 0 && task->priority < queue->tasks[(i - 1) / 2]->priority) {
		queue->tasks[i] = queue->tasks[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	queue->tasks[i] = task;
	queue->size++;
	return true;
}

Task* dequeue(PriorityQueue* queue) {
	if (isEmpty) { return nullptr; }

	Task* result = queue->tasks[0];
	queue->size--;

	Task* lastTask = queue->tasks[queue->size];
	int i = 0;
	while ((2 * i + 1) < queue->size) {
		int child = (2 * i + 1);
		if (child + 1 < queue->size && queue->tasks[child + 1]->priority < queue->tasks[child]->priority) {
			child++;
		}

		if (lastTask->priority <= queue->tasks[child]->priority) {
			break;
		}

		queue->tasks[i] = queue->tasks[child];
		i = child;
	}

	queue->tasks[i] = lastTask;
	return result;
}
Task* getTaskAtIndex(PriorityQueue* queue, int idx) {
	if (idx > 0 && idx < queue->size) {
		return queue->tasks[idx];
	}

	return nullptr;
}

void freePriorityQueue(PriorityQueue* queue) {
	for (int i = 0; i < MAX_TASK_COUNT; i++) {
		if (queue->tasks[i]) {
			freeTask(queue->tasks[i]);
		}
	}

	free(queue);
	queue = nullptr;
}

#endif

