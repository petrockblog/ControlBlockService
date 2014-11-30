#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

class InputDevice {
public:
	typedef enum {
		CHANNEL_1 = 0,
		CHANNEL_2,
		CHANNEL_UNDEFINED
	} Channel_e;

	InputDevice() {};
	virtual ~InputDevice() {};

	virtual void initialize(Channel_e channel) = 0;
	virtual void update() = 0;
};

#endif