#ifndef __I2CDEVICE_C__
#define __I2CDEVICE_C__

#include <Wire.h>
#include "../../Kernel/IO/i2cDevice.h"
#include "../../Kernel/Threading/task.h"

int nextI2CDevice;


Task* createListenTask() {
	Task* task;
	createTask(task, listenI2CBus, 100);
	setLongrunningTaskState(task);

	task->init = initBus;

	return task;
}

int listenI2CBus(Task* task) {
	if (nextI2CDevice > I2CDEVICE_COUNT) {
		nextI2CDevice = 0;
	}

	I2CDevice* device = i2cDevices[nextI2CDevice];

	if (device && device->dataReceiveCallback != nullptr) {
		int data = Wire.requestFrom(device->addr);
		if (data) {
			device->dataReceivedSize = data;
			device->dataReceiveCallback(data);
		}
		else { device->dataReceivedSize = -1; }
	}

	nextI2CDevice++;
}

void initBus() {
	for (int i = 0; i < I2CDEVICE_COUNT; i++) {
		I2CDevice* device = (I2CDevice*)malloc(sizeof(I2CDevice));
		if (!device) {
			free(device);
			continue;
		}

		i2cDevices[i] = device;
		i2cDevices[i]->dataReceiveCallback = nullptr;
	}
}

I2CDevice* getDeviceAtAddr(int addr) {
	for (int i = 0; i < I2CDEVICE_COUNT; i++) {
		if (i2cDevices[i] && i2cDevices[i]->addr == addr) {
			return i2cDevices[i];
		}
	}

	return nullptr;
}

I2CDevice* setDevice(int addr) {
	for (var i = 0; i < I2CDEVICE_COUNT; i++) {
		if (!i2cDevices[i] || i2cDevices[i]->addr == -1) {
			i2cDevices[i]->addr = addr;
			return i2cDevices[i];
		}
	}

	return nullptr;
}

void freeI2CBus() {
	for (int i = 0; i < I2CDEVICE_COUNT; i++) {
		I2CDEVICE* device = i2cDevice[i];
		if (device) {
			free(device);
		}
	}

	free(i2cDevices);
}

void sendData(int addr, int data) {
	I2CDevice* device = getDeviceAtAddr(addr);
	if (device) {
		Wire.beginTransmission(addr);
		Wire.write(data);
		Wire.endTransmission();
	}
}


#endif

