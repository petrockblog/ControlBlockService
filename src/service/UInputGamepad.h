#ifndef UINPUTGAMEPAD_H
#define UINPUTGAMEPAD_H

#include <stdint.h>

class UInputGamepad {
public:
	UInputGamepad();
	~UInputGamepad();

	void setKeyState(uint16_t keycode,int16_t keyvalue, uint16_t evtype);

private:
	int32_t uinp_fd;

};

#endif // UINPUTGAMEPAD_H
