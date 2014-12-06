#include "MAMEGamepad.h"

MAMEGamepad::MAMEGamepad() {
}

MAMEGamepad::~MAMEGamepad() {
	UInputcpp::releaseHandle(uinp_fd);	
}

void MAMEGamepad::initialize(InputDevice::Channel_e channel) {
	DigitalIn::getInstance().setMode(DigitalIn::DI_MODE_ALLIN);

	uinp_fd = UInputcpp::getHandle();
	this->channel = channel;

	struct uinput_user_dev uinp;
	memset(&uinp, 0, sizeof(uinp));
	strncpy(uinp.name, "ControlBlock Keyboard", strlen("ControlBlock Keyboard"));
	uinp.id.version = 4;
	uinp.id.bustype = BUS_USB;
	uinp.id.product = 1;
	uinp.id.vendor = 1;

	// Setup the uinput device
	// keyboard
	ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
	ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);
	int i = 0;
	for (i = 0; i < 256; i++) {
		ioctl(uinp_fd, UI_SET_KEYBIT, i);
	}

	/* Create input device into input sub-system */
	write(uinp_fd, &uinp, sizeof(uinp));
	if (ioctl(uinp_fd, UI_DEV_CREATE)) {
		printf("[MAMEGamepad] Unable to create UINPUT device.");
		throw -1;
	}
}

void MAMEGamepad::update() {
	DigitalIn di = DigitalIn::getInstance();

	if (channel == InputDevice::CHANNEL_1) {
		// axes
		UInputcpp::setKeyState(uinp_fd, KEY_LEFT, di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_RIGHT, di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_UP, di.getLevel(DigitalIn::DI_CHANNEL_P1_UP) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_DOWN, di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

		// buttons
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTCTRL, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTALT, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_SPACE, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTSHIFT, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_Z, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_X, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_C, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_V, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_1, di.getLevel(DigitalIn::DI_CHANNEL_P1_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_5, di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_P, di.getLevel(DigitalIn::DI_CHANNEL_P1_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_ENTER, di.getLevel(DigitalIn::DI_CHANNEL_P1_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else if (channel == InputDevice::CHANNEL_2) {
		// axes
		UInputcpp::setKeyState(uinp_fd, KEY_D, di.getLevel(DigitalIn::DI_CHANNEL_P2_LEFT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_G, di.getLevel(DigitalIn::DI_CHANNEL_P2_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_R, di.getLevel(DigitalIn::DI_CHANNEL_P2_UP) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_F, di.getLevel(DigitalIn::DI_CHANNEL_P2_DOWN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

		// buttons
		UInputcpp::setKeyState(uinp_fd, KEY_A, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_S, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_Q, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_W, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_I, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_K, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_J, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_L, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_2, di.getLevel(DigitalIn::DI_CHANNEL_P2_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_6, di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_TAB, di.getLevel(DigitalIn::DI_CHANNEL_P2_A) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_ESC, di.getLevel(DigitalIn::DI_CHANNEL_P2_B) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else {
		throw 3;
	}
}

