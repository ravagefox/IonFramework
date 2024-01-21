
#include <Arduino.h>
#include "taskScheduler.c";
#include "systemClock.c";

TaskScheduler* systemScheduler;
Task* systemClock;

void setup() {
	initTaskScheduler(systemScheduler);

	systemClock = createSystemClock();
	if (!systemClock || !enqueue(systemScheduler->queue, systemClock)) {
		freeTask(systemClock);
	}
}

void loop() {
	runScheduler(systemScheduler, millis());
}