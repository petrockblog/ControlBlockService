#include <chrono>
#include <thread>

#include "SNESGamepad.h"

SNESGamepad::SNESGamepad() : channel(InputDevice::CHANNEL_UNDEFINED), uinp_fd(0) {
}

SNESGamepad::~SNESGamepad() {
	if (uinp_fd != 0) {
		UInputcpp::releaseHandle(uinp_fd);
	}
}

void SNESGamepad::initialize(InputDevice::Channel_e channel) {
	uinp_fd = UInputcpp::getHandle();
	this->channel = channel;

	struct uinput_user_dev uinp;
	memset(&uinp, 0, sizeof(uinp));
	strncpy(uinp.name, "ControlBlock Gamepad", strlen("ControlBlock Gamepad"));
	uinp.id.version = 4;
	uinp.id.bustype = BUS_USB;
	uinp.id.product = 1;
	uinp.id.vendor = 1;

	// Setup the uinput device
	ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);

	// gamepad, buttons
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_A);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_B);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_X);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Y);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_START);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_SELECT);

	// gamepad, directions
	ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
	ioctl(uinp_fd, UI_SET_ABSBIT, ABS_X);
	ioctl(uinp_fd, UI_SET_ABSBIT, ABS_Y);
	uinp.absmin[ABS_X] = 0;
	uinp.absmax[ABS_X] = 4;
	uinp.absmin[ABS_Y] = 0;
	uinp.absmax[ABS_Y] = 4;

	/* Create input device into input sub-system */
	write(uinp_fd, &uinp, sizeof(uinp));
	if (ioctl(uinp_fd, UI_DEV_CREATE)) {
		printf("[ArcadeGamepad] Unable to create UINPUT device.");
		// throw -1;
	}

	UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
	UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);

	DigitalOut dout = DigitalOut::getInstance();
	if (channel == InputDevice::CHANNEL_1) {
		dout.setLevel(DigitalOut::DO_CHANNEL_P1_STROBE, DigitalOut::DO_LEVEL_LOW);
		dout.setLevel(DigitalOut::DO_CHANNEL_P1_CLOCK, DigitalOut::DO_LEVEL_LOW);
		dout.setLevel(DigitalOut::DO_CHANNEL_P1_VCC, DigitalOut::DO_LEVEL_HIGH);
	} else {
		dout.setLevel(DigitalOut::DO_CHANNEL_P2_STROBE, DigitalOut::DO_LEVEL_LOW);
		dout.setLevel(DigitalOut::DO_CHANNEL_P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
		dout.setLevel(DigitalOut::DO_CHANNEL_P2_VCC, DigitalOut::DO_LEVEL_HIGH);
	}
}

uint16_t SNESGamepad::getSNESControllerState() {
	uint16_t state = 0;

	DigitalIn din = DigitalIn::getInstance();
	DigitalOut dout = DigitalOut::getInstance();

	if (channel == InputDevice::CHANNEL_1) {
		dout.setLevel(DigitalOut::DO_CHANNEL_P1_STROBE, DigitalOut::DO_LEVEL_HIGH);
		std::this_thread::sleep_for(std::chrono::microseconds(2));
		dout.setLevel(DigitalOut::DO_CHANNEL_P1_STROBE, DigitalOut::DO_LEVEL_LOW);
		std::this_thread::sleep_for(std::chrono::microseconds(2));

		for (uint8_t i = 0; i < 16; i++) {
			DigitalIn::DI_Level_e curpin = din.getLevel(DigitalIn::DI_CHANNEL_P1_DATA); 
			if (curpin == DigitalIn::DI_LEVEL_LOW) {
				state |= (1 << i);
			}

			dout.setLevel(DigitalOut::DO_CHANNEL_P1_CLOCK, DigitalOut::DO_LEVEL_HIGH);
			std::this_thread::sleep_for(std::chrono::microseconds(2));
			dout.setLevel(DigitalOut::DO_CHANNEL_P1_CLOCK, DigitalOut::DO_LEVEL_LOW);
			std::this_thread::sleep_for(std::chrono::microseconds(2));
		}
	} else {
		dout.setLevel(DigitalOut::DO_CHANNEL_P2_STROBE, DigitalOut::DO_LEVEL_HIGH);
		std::this_thread::sleep_for(std::chrono::microseconds(2));
		dout.setLevel(DigitalOut::DO_CHANNEL_P2_STROBE, DigitalOut::DO_LEVEL_LOW);
		std::this_thread::sleep_for(std::chrono::microseconds(2));

		for (uint8_t i = 0; i < 16; i++) {
			DigitalIn::DI_Level_e curpin = din.getLevel(DigitalIn::DI_CHANNEL_P2_DATA); 
			if (curpin == DigitalIn::DI_LEVEL_LOW) {
				state |= (1 << i);
			}

			dout.setLevel(DigitalOut::DO_CHANNEL_P2_CLOCK, DigitalOut::DO_LEVEL_HIGH);
			std::this_thread::sleep_for(std::chrono::microseconds(2));
			dout.setLevel(DigitalOut::DO_CHANNEL_P2_CLOCK, DigitalOut::DO_LEVEL_LOW);
			std::this_thread::sleep_for(std::chrono::microseconds(2));
		}
	}

	// set to 0 if the controller is not connected
	if ((state & 0xFFF) == 0xFFF) {
		state = 0;
	}
	return state;
}

void SNESGamepad::update() {
	DigitalIn di = DigitalIn::getInstance();

	uint16_t state = getSNESControllerState();

	// axes
	if ((state & GPAD_SNES_LEFT) == GPAD_SNES_LEFT) {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
	} else if ((state & GPAD_SNES_RIGHT) == GPAD_SNES_RIGHT) {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
	} else {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
	}
	if ((state & GPAD_SNES_UP) == GPAD_SNES_UP) {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
	} else if ((state & GPAD_SNES_DOWN) == GPAD_SNES_DOWN) {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
	} else {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
	}

	// buttons
	UInputcpp::setKeyState(uinp_fd, BTN_A, (state & GPAD_SNES_A) == GPAD_SNES_A ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_B, (state & GPAD_SNES_B) == GPAD_SNES_B ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_X, (state & GPAD_SNES_X) == GPAD_SNES_X ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_Y, (state & GPAD_SNES_Y) == GPAD_SNES_Y ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_TL, (state & GPAD_SNES_L) == GPAD_SNES_L ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_TR, (state & GPAD_SNES_R) == GPAD_SNES_R ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_START, (state & GPAD_SNES_START) == GPAD_SNES_START ? 0 : 1, EV_KEY);
	UInputcpp::setKeyState(uinp_fd, BTN_SELECT, (state & GPAD_SNES_SELECT) == GPAD_SNES_SELECT ? 0 : 1, EV_KEY);
}
