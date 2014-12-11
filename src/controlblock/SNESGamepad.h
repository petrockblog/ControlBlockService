#ifndef SNESGAMEPAD_H
#define SNESGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"
#include "DigitalIn.h"
#include "DigitalOut.h"

class SNESGamepad : public InputDevice {
public:
	/* bit masks for checking the button states for SNES controllers */
	static const uint16_t GPAD_SNES_B =       0x01;
	static const uint16_t GPAD_SNES_Y =       0x02;
	static const uint16_t GPAD_SNES_SELECT =  0x04;
	static const uint16_t GPAD_SNES_START =   0x08;
	static const uint16_t GPAD_SNES_UP =      0x10;
	static const uint16_t GPAD_SNES_DOWN =    0x20;
	static const uint16_t GPAD_SNES_LEFT =    0x40;
	static const uint16_t GPAD_SNES_RIGHT =   0x80;
	static const uint16_t GPAD_SNES_A =       0x100;
	static const uint16_t GPAD_SNES_X =       0x200;
	static const uint16_t GPAD_SNES_L =       0x400;
	static const uint16_t GPAD_SNES_R =       0x800;

	/* bit masks for checking the button states for NES controllers */
	static const uint16_t GPAD_NES_B =       0x01;
	static const uint16_t GPAD_NES_SELECT =  0x04;
	static const uint16_t GPAD_NES_START =   0x08;
	static const uint16_t GPAD_NES_UP =      0x10;
	static const uint16_t GPAD_NES_DOWN =    0x20;
	static const uint16_t GPAD_NES_LEFT =    0x40;
	static const uint16_t GPAD_NES_RIGHT =   0x80;
	static const uint16_t GPAD_NES_A =       0x100;

	SNESGamepad();
	~SNESGamepad();

	virtual void initialize(InputDevice::Channel_e channel);
	virtual void update();

private:
	static const uint32_t STROBEDELAY = 1;

	InputDevice::Channel_e channel;
	uint32_t uinp_fd;

	uint16_t getSNESControllerState();
};

#endif
