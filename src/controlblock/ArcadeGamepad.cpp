#include "ArcadeGamepad.h"

extern "C" {
	#include <linux/input.h>
	#include <linux/uinput.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
}

ArcadeGamepad::ArcadeGamepad() : channel(InputDevice::CHANNEL_UNDEFINED), uinp_fd(0) {
}

ArcadeGamepad::~ArcadeGamepad() {
	UInputcpp::releaseHandle(uinp_fd);
}

void ArcadeGamepad::initialize(InputDevice::Channel_e channel) {
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
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_C);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_X);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Y);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Z);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL2);
	ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR2);
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
		throw -1;
	}

	UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
	UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
}

void ArcadeGamepad::update() {
	DigitalIn di = DigitalIn::getInstance();
	// axes
	if (di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT) == DigitalIn::DI_LEVEL_HIGH) {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
	} else if (di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT) == DigitalIn::DI_LEVEL_HIGH) {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
	} else {
		UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
	}
	if (di.getLevel(DigitalIn::DI_CHANNEL_P1_UP) == DigitalIn::DI_LEVEL_HIGH) {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
	} else if (di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN) == DigitalIn::DI_LEVEL_HIGH) {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
	} else {
		UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
	}

	// buttons
	if (channel == InputDevice::CHANNEL_1) {
		UInputcpp::setKeyState(uinp_fd, BTN_A, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_B, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_C, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_X, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_Y, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_Z, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TL, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TR, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_START, di.getLevel(DigitalIn::DI_CHANNEL_P1_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_SELECT, di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TL2, di.getLevel(DigitalIn::DI_CHANNEL_P1_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TR2, di.getLevel(DigitalIn::DI_CHANNEL_P1_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else if (channel == InputDevice::CHANNEL_2) {
		UInputcpp::setKeyState(uinp_fd, BTN_A, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_B, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_C, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_X, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_Y, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_Z, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TL, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TR, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_START, di.getLevel(DigitalIn::DI_CHANNEL_P2_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_SELECT, di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TL2, di.getLevel(DigitalIn::DI_CHANNEL_P2_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, BTN_TR2, di.getLevel(DigitalIn::DI_CHANNEL_P2_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else {
		throw 3;
	}
}
