#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include "PowerSwitch.h"
#include "InputDevice.h"
#include "ControlBlockConfiguration.h"

class ControlBlock {
public:
	static const uint8_t NUMGAMEPADS = 2;

	ControlBlock();
	~ControlBlock();

	void initialize();
	void update();

private:
	PowerSwitch* powerSwitch;
	InputDevice* gamepads[NUMGAMEPADS];
	ControlBlockConfiguration* configuration;

};

#endif // CONTROLBLOCK_H
