#ifndef __I2CDEVICE__
#define __I2CDEVICE__

#include "../kernel.h"
#include "../Threading/task.h"


typedef struct {
	int addr;
	int dataReceivedSize;
	void (*dataReceiveCallback)(int);
} I2CDevice;


I2CDevice* i2cDevices[I2CDEVICE_COUNT];


Task* createListenTask();
void initBus();
int listenI2CBus(Task* task);
void freeI2CBus();

I2CDevice* getDeviceAtAddr(int addr);
I2CDevice* setDevice(int addr);

void sendData(int addr, int data);


#endif

