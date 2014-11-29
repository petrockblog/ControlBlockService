#include "DigitalOut.h"
extern "C" {
	#include <wiringPi.h>
}
#include <stdint.h>

DigitalOut::DigitalOut() {
	wiringPiSetup ();
	pinMode (0, OUTPUT) ;
}

DigitalOut::~DigitalOut() {
}

void DigitalOut::setLevel(DO_Channel_e channel, DO_Level_e level) {
	int32_t outlevel;
	int32_t pin = -1;

	if (level == DO_LEVEL_LOW) {
		outlevel = LOW;
	} else {
		outlevel = HIGH;
	}

	if (channel == DO_CHANNEL_TOPOWERSWITCH) {
		pin = 0;
	}

	if (pin != -1) {
		digitalWrite(pin, outlevel);
	}
}
