#include <linux/uinput.h>

#include "MAMEGamepad.h"
#include "uinputcpp.h"
#include "GPIO.h"

MAMEGamepad::MAMEGamepad() {
}

MAMEGamepad::~MAMEGamepad() {
	UInputcpp::releaseHandle(uinp_fd);	
}

void MAMEGamepad::initialize(InputDevice::Channel_e channel) {
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

	GPIO& gpio = GPIO::getInstance();
	for (int32_t i = 0 ; i < 16 ; ++i) {
		gpio.setDirection (100 + i, GPIO::DIRECTION_IN);
		gpio.setDirection (200 + i, GPIO::DIRECTION_IN);
		gpio.setPullupMode(100 + i, GPIO::PULLUP_ENABLED);
		gpio.setPullupMode(200 + i, GPIO::PULLUP_ENABLED);
	}		
}

void MAMEGamepad::update() {
	GPIO& gpio = GPIO::getInstance();

	if (channel == InputDevice::CHANNEL_1) {
		// axes
		UInputcpp::setKeyState(uinp_fd, KEY_LEFT, gpio.read(101) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_RIGHT, gpio.read(100) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_UP, gpio.read(102) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_DOWN, gpio.read(103) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);

		// buttons
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTCTRL, gpio.read(104) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTALT, gpio.read(105) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_SPACE, gpio.read(106) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_LEFTSHIFT, gpio.read(107) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_Z, gpio.read(200) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_X, gpio.read(201) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_C, gpio.read(202) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_V, gpio.read(203) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_1, gpio.read(204) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_5, gpio.read(205) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_P, gpio.read(206) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_ENTER, gpio.read(207) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else if (channel == InputDevice::CHANNEL_2) {
		// axes
		UInputcpp::setKeyState(uinp_fd, KEY_D, gpio.read(114) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_G, gpio.read(115) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_R, gpio.read(113) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_F, gpio.read(112) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);

		// buttons
		UInputcpp::setKeyState(uinp_fd, KEY_A, gpio.read(111) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_S, gpio.read(110) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_Q, gpio.read(109) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_W, gpio.read(108) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_I, gpio.read(215) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_K, gpio.read(214) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_J, gpio.read(213) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_L, gpio.read(212) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_2, gpio.read(211) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_6, gpio.read(210) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_TAB, gpio.read(209) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);
		UInputcpp::setKeyState(uinp_fd, KEY_ESC, gpio.read(208) == GPIO::LEVEL_LOW ? 0 : 1, EV_KEY);	
	} else {
		throw 3;
	}
}

