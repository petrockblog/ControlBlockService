#include "UInputGamepad.h"

extern "C" {
	#include <linux/input.h>
	#include <linux/uinput.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
}

UInputGamepad::UInputGamepad() {
	uinp_fd = open("/dev/uinput", O_WRONLY | O_NDELAY);
	if (uinp_fd == 0) {
		printf("Unable to open /dev/uinput\n");
		throw -1;
	}

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
		printf("[UInputGamepad] Unable to create UINPUT device.");
		throw -1;
	}

	setKeyState(ABS_X, 2, EV_ABS);
	setKeyState(ABS_Y, 2, EV_ABS);
}

UInputGamepad::~UInputGamepad() {
	ioctl(uinp_fd, UI_DEV_DESTROY);
	close(uinp_fd);	
}

void UInputGamepad::setKeyState(uint16_t keycode, int16_t keyvalue, uint16_t evtype) {
	struct input_event event;
	gettimeofday(&event.time, NULL);

	event.type = evtype;
	event.code = keycode;
	event.value = keyvalue;

	if (write(uinp_fd, &event, sizeof(event)) < 0) {
		printf("[UInputGamepad] Simulate key error\n");
	}

	event.type = EV_SYN;
	event.code = SYN_REPORT;
	event.value = 0;
	write(uinp_fd, &event, sizeof(event));
	if (write(uinp_fd, &event, sizeof(event)) < 0) {
		printf("[UInputGamepad] Simulate key error\n");
	}
}
