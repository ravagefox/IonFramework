#ifndef __PINOUT_DEVICE__
#define __PINOUT_DEVICE__



typedef struct {
	int pinCount;
	PinMode pins[];

} PinoutDevice;

typedef struct {
	int pin;
	int mode;
} PinMode;




PinoutDevice* createPinout(int pinCount);
void setPinmode(PinoutDevice* device, int pin, int mode);
void freePinout(PinoutDevice* device);



#endif


