#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include <stdlib.h>
#include <linux/uinput.h>
#include "PowerSwitch.h"
#include "UInputGamepad.h"
#include "DigitalIn.h"

class ControlBlock
{
public:

	static const uint8_t NUMGAMEPADS = 2;

	ControlBlock();
	~ControlBlock();

	void update();

private:
	PowerSwitch powerSwitch;
	UInputGamepad* gamepads[NUMGAMEPADS];

	void updateGamepads();
	void updatePowerSwitch();

};

#endif // CONTROLBLOCK_H
