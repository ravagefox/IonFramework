#ifndef __SYSTEM_CLOCK_C__
#define __SYSTEM_CLOCK_C__

#include <Arduino.h>
#include "../Kernel/systemClock.h"

unsigned long environmentTicks;

Task* createSystemClock() {
	Task* clockFunc;
	createTask(clockFunc, systemTickFunc, 1000);
	setLongrunningTaskState(clockFunc);
	clockFunc->priority = TASK_PRIORITY_HIGH;

	return clockFunc;
}

void initSystemClock() {
	environmentTicks = millis();
}

int systemTickFunc(Task* task) {
	environmentTicks = millis();
	return 0;
}


#endif

