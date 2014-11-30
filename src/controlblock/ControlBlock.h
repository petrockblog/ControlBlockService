#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <stdint.h>
#include <iostream>
#include <wiringPi.h>
#include <mcp23017.h>
#include "PowerSwitch.h"
#include "InputDevice.h"
#include "ArcadeGamepad.h"
#include "SNESGamepad.h"
#include "ControlBlockConfiguration.h"

class ControlBlock {
public:
	static const uint8_t NUMGAMEPADS = 2;
	const uint32_t MCPBASE1 = 100;
	const uint32_t MCPBASE2 = 116;
	static const uint8_t MCP1ADDRESS = 0x20;
	static const uint8_t MCP2ADDRESS = 0x27;

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
