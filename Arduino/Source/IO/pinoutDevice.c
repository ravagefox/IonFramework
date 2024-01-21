#ifndef __PINOUT_DEVICE_C__
#define __PINOUT_DEVICE_C__


#include "../../Kernel/IO/pinoutDevice.h"

PinoutDevice* createPinout(int pinCount) {
	PinoutDevice* device = (PinoutDevice*)malloc(sizeof(PinoutDevice) + (pinCount * sizeof(PinMode));
	if (!device) {
		free(device);
		return nullptr;
	}

	device->pinCount = pinCount;
	for (int i = 0; i < pinCount; i++) {
		device->pins[i].pin = i;
		device->pins[i].mode = 0;
	}

	return device;
}

void setPinmode(PinoutDevice* device, int pin, int mode) {
	if (pin >= 0 && pin < device->pinCount) {
		device->pins[pin].mode = mode;
	}
}

void freePinout(PinoutDevice* device) {
	free(device);
}



#endif

