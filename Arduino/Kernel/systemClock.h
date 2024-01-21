#ifndef __SYSTEM_CLOCK__
#define __SYSTEM_CLOCK__

#include "Threading/task.h"


Task* createSystemClock();
int systemTickFunc(Task* task);


#endif

