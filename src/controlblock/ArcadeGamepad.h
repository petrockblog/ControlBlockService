#ifndef ARCADEGAMEPAD_H
#define ARCADEGAMEPAD_H

#include <stdint.h>
#include <linux/uinput.h>
#include "InputDevice.h"
#include "DigitalIn.h"
#include "uinputcpp.h"

class ArcadeGamepad : public InputDevice {
public:
	ArcadeGamepad();
	~ArcadeGamepad();

	virtual void initialize(InputDevice::Channel_e channel);
	virtual void update();

private:
	InputDevice::Channel_e channel;
	uint32_t uinp_fd;

};

#endif