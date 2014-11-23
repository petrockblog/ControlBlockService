#include <stdio.h>
#include <chrono>
#include <thread>

#include "ControlBlock.h"
#include "PowerSwitch.h"

int main(int argc, char **argv)
{
	ControlBlock controlBlock = ControlBlock();

	while (true) {
		controlBlock.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}
