#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include "kernel.h"
#include "Threading/task.h"


typedef struct {
	int size;
	Task* tasks[MAX_TASK_COUNT];

} PriorityQueue;


void initPriorityQueue(PriorityQueue* queue);
bool isEmpty(PriorityQueue* queue);
bool enqueue(PriorityQueue* queue, Task* task);
Task* dequeue(PriorityQueue* queue);
Task* getTaskAtIndex(PriorityQueue* queue, int idx);
void freePriorityQueue(PriorityQueue* queue);


#endif

