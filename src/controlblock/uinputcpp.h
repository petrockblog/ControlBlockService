#ifndef UINPUTCPP_H
#define UINPUTCPP_H

#include <stdint.h>
extern "C" {
	#include <linux/input.h>
	#include <linux/uinput.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
}

class UInputcpp {
public:
	UInputcpp() {};
	~UInputcpp() {};

	static int32_t getHandle() {
		int32_t handle = open("/dev/uinput", O_WRONLY | O_NDELAY);
		if (handle == 0) {
			printf("Unable to open /dev/uinput\n");
			throw 1;
		}
		return handle;
	}

	static void releaseHandle(int32_t handle) {
		ioctl(handle, UI_DEV_DESTROY);
		close(handle);	
	}

	static void setKeyState(int32_t uinp_fd, uint16_t keycode, int16_t keyvalue, uint16_t evtype) {
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

private:

};

#endif