/*
 * (c) Copyright 2014  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlockService
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

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
