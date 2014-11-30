#ifndef UINPUTGAMEPAD_H
#define UINPUTGAMEPAD_H

#include <stdint.h>
#include <linux/uinput.h>
#nclude "InputDevice.h"
#include "DigitalIn.h"

class UInputGamepad : public InputDevice {
public:
	typedef enum {
		GAMEPADTYPE_ARCADE = 0
	} GamepadType_e;

	UInputGamepad(GamepadType_e type);
	~UInputGamepad();
	virtual void initialize();
	virtual void update();

private:
	int32_t uinp_fd;

	void setKeyState(uint16_t keycode,int16_t keyvalue, uint16