#ifndef __TASK__
#define __TASK__

#define TASK_STATE_IDLE		0b00000001
#define TASK_STATE_ERR      0b00000010
#define TASK_STATE_LONGRUN  0b00000100
#define TASK_STATE_PAUSE    0b00001000
#define TASK_STATE_ENDREQ   0b00010000
#define TASK_STATE_WAITING  0b00100000

#define TASK_PRIORITY_HIGH			 0
#define TASK_PRIORITY_MED			 1
#define TASK_PRIORITY_LOW			 2
#define TASK_PRIORITY_SYSTEM		 3


typedef struct {
	int (*function)(struct Task*);
	void (*init)(void);
	unsigned long interval;
	unsigned long last_execution;
	int state;
	int priority;

} Task;

const Task EmptyTask = {
	nullptr,			// init
	nullptr,			// function
	0,					// interval
	0,					// last_execution
	TASK_STATE_IDLE,	// state
	TASK_PRIORITY_LOW,	// priority
}

void toggleTaskState(Task* task, int state);
void pauseTask(Task* task);
void resumeTask(Task* task);
void startTask(Task* task);
void endTask(Task* task);
void setLongrunningTaskState(Task* task);
void freeTask(Task* task);
bool executeTask(Task* task, const unsigned long environmentTicks);

void createTask(Task* task, int (*function)(struct Task*), unsigned long interval);

#endif

