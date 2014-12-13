#ifndef SNESGAMEPAD_H
#define SNESGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"

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
	const uint16_t PIN_P1_VCC = 115;
	const uint16_t PIN_P1_LATCH = 114;
	const uint16_t PIN_P1_CLOCK = 113;
	const uint16_t PIN_P1_DATA = 112;
	const uint16_t PIN_P2_VCC = 111;
	const uint16_t PIN_P2_LATCH = 110;
	const uint16_t PIN_P2_CLOCK = 109;
	const uint16_t PIN_P2_DATA = 108;

	InputDevice::Channel_e channel;
	uint32_t uinp_fd;
	static uint16_t state1;
	static uint16_t state2;

	uint16_t getSNESControllerState();
};

#endif
