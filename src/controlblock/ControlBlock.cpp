#include "ControlBlock.h"

ControlBlock::ControlBlock() : configuration(new ControlBlockConfiguration())  
{
	std::map <ControlBlockConfiguration::ShutdownType_e, PowerSwitch::ShutdownActivated_e> switchMapping;
	switchMapping[ControlBlockConfiguration::SHUTDOWN_ACTIVATED] = PowerSwitch::SHUTDOWN_ACTIVATED;
	switchMapping[ControlBlockConfiguration::SHUTDOWN_DEACTIVATED] = PowerSwitch::SHUTDOWN_DEACTIVATED;

	wiringPiSetup ();
	mcp23017Setup (MCPBASE1, MCP1ADDRESS);
	mcp23017Setup (MCPBASE2, MCP2ADDRESS);

	configuration->initialize();

	powerSwitch = new PowerSwitch(switchMapping[configuration->getShutdownActivation()]);
	for (uint8_t counter = 0; counter<NUMGAMEPADS; counter++) {
		if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_ARCADE) {
			gamepads[counter] = new ArcadeGamepad();
		} else if (configuration->getGamepadType() == ControlBlockConfiguration::GAMEPAD_SNES) {
			gamepads[counter] = new SNESGamepad();
		}
		gamepads[counter]->initialize(counter==0 ? InputDevice::CHANNEL_1 : InputDevice::CHANNEL_2);
	}
}

ControlBlock::~ControlBlock() {
	for (uint8_t counter = 0; counter<NUMGAMEPADS; counter++) {
		delete gamepads[counter];
		gamepads[counter] = 0;
	}
	delete powerSwitch;
	delete configuration;
}

void ControlBlock::update() {
	try {
		for (uint8_t counter = 0; counter<NUMGAMEPADS; counter++) {
			gamepads[counter]->update();
		}
	} catch (int errno) {
		std::cout << "Error while updating the gamepad devices. Error number: " << errno << std::endl;
	}
	try {
		powerSwitch->update();
	} catch (int errno) {
		std::cout << "Error while updating the power switch instance. Error number: " << errno << std::endl;
	}
}
