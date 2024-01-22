#ifndef __KERNEL__
#define __KERNEL__


// TODO: update the architecture to match the device platform
#define ARCHITECTURE 0x08

#define ARCHITECTURE_x8   0x08
#define ARCHITECTURE_x16  0x16
#define ARCHITECTURE_x32  0x32



// 8 bits shifted by the size of 2 which is the size of an int, then 16 bit shifted by 2, etc...
#define I2CDEVICE_COUNT (ARCHITECTURE == ARCHITECTURE_x8 ? 8 << 2 : ARCHITECTURE == ARCHITECTURE_x16 ? 16 << 2 : 32 << 4)
// 16 tasks shifted by the size of 2 which is the size of an int, then 24 shifted by 2, etc...
#define MAX_TASK_COUNT (ARCHITECTURE == ARCHITECTURE_x8 ? 16 << 2 : ARCHITECTURE == ARCHITECTURE_x16 ? 24 << 2 : 48 << 2)




// TODO: change the hardware identifier when compiling for new hardware
#define HWDID { 0x82, 0x7a, 0xab, 0x3a, 0x71, 0xe3, 0xc, 0x3e }

// TODO: change the software identifier when compiling for new hardware
#define SFTID { 0xb0, 0x99, 0xff, 0xd2, 0x52, 0x31, 0xd7, 0x55 }





#endif

