#ifndef CONTROLBLOCKCONFIGURATION_H
#define CONTROLBLOCKCONFIGURATION_H

#include <json/json.h>

class ControlBlockConfiguration {
public:
	typedef enum {
		GAMEPAD_ARCADE = 0,
		GAMEPAD_MAME,
		GAMEPAD_SNES
	} GamepadType_e;

	typedef enum {
		SHUTDOWN_DEACTIVATED = 0,
		SHUTDOWN_ACTIVATED
	} ShutdownType_e;

	ControlBlockConfiguration();
	~ControlBlockConfiguration();
	
	void initialize();
	GamepadType_e getGamepadType() const;
	ShutdownType_e getShutdownActivation() const;

private:
	GamepadType_e gamepadType;
	ShutdownType_e doShutdown;

};

#endif
