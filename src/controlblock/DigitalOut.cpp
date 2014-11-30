#include "DigitalOut.h"
extern "C" {
	#include <wiringPi.h>
	#include <mcp23017.h>
}
#include <stdint.h>

DigitalOut::DigitalOut() : mode(DO_MODE_ONLYPOWERSWITCH) {
	setMode(mode);
}

DigitalOut::~DigitalOut() {
}

void DigitalOut::setMode(DO_Mode_e mode) {
	this->mode = mode;

	switch (mode) {
		case DO_MODE_ONLYPOWERSWITCH:
			pinMode (0, OUTPUT);
			break;
		case DO_MODE_SNES:
			pinMode (0, OUTPUT);
			pinMode (MCPBASE1 + 0, OUTPUT);
			pinMode (MCPBASE1 + 1, OUTPUT);
			pinMode (MCPBASE1 + 2, OUTPUT);
			pinMode (MCPBASE1 + 13, OUTPUT);
			pinMode (MCPBASE1 + 14, OUTPUT);
			pinMode (MCPBASE1 + 15, OUTPUT);
			digitalWrite(MCPBASE1 + 0, LOW);
			digitalWrite(MCPBASE1 + 1, LOW);
			digitalWrite(MCPBASE1 + 2, LOW);
			digitalWrite(MCPBASE1 + 13, LOW);
			digitalWrite(MCPBASE1 + 14, LOW);
			digitalWrite(MCPBASE1 + 15, LOW);			
			break;
	}
}

void DigitalOut::setLevel(DO_Channel_e channel, DO_Level_e level) {
	int32_t outlevel;

	if (level == DO_LEVEL_LOW) {
		outlevel = LOW;
	} else {
		outlevel = HIGH;
	}

	switch (channel) {
		case DO_CHANNEL_TOPOWERSWITCH:
			digitalWrite(0, outlevel);
			break;
	    case DO_CHANNEL_P1_STROBE:
	    	digitalWrite(MCPBASE1 + 1, outlevel);
	    	break;
	    case DO_CHANNEL_P1_CLOCK:
	    	digitalWrite(MCPBASE1 + 2, outlevel);
	    	break;
	    case DO_CHANNEL_P1_VCC:
	    	digitalWrite(MCPBASE1 + 0, outlevel);
	    	break;
	    case DO_CHANNEL_P2_STROBE:
	    	digitalWrite(MCPBASE1 + 14, outlevel);
	    	break;
	    case DO_CHANNEL_P2_CLOCK:
	    	digitalWrite(MCPBASE1 + 13, outlevel);
	    	break;
	    case DO_CHANNEL_P2_VCC:
	    	digitalWrite(MCPBASE1 + 14, outlevel);
	    	break;
	}
}
