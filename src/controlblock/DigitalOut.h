#ifndef DIGITALOUT_H
#define DIGITALOUT_H

#include "bcm2835.h"
#include <stdint.h>
#include "mcp23017pi.h"

class DigitalOut {
public:
	typedef enum {
	    DO_CHANNEL_TOPOWERSWITCH = 0,
	    DO_CHANNEL_P1_STROBE,
	    DO_CHANNEL_P1_CLOCK,
	    DO_CHANNEL_P1_VCC,
	    DO_CHANNEL_P2_STROBE,
	    DO_CHANNEL_P2_CLOCK,
	    DO_CHANNEL_P2_VCC,
	} DO_Channel_e;

	typedef enum {
	    DO_LEVEL_LOW = 0,
	    DO_LEVEL_HIGH
	} DO_Level_e;

	typedef enum {
		DO_MODE_ONLYPOWERSWITCH = 0,
		DO_MODE_SNES
	} DO_Mode_e;

	~DigitalOut();

	static DigitalOut& getInstance() {
		static DigitalOut digitalOut = DigitalOut();
		return digitalOut;
	}

	void setMode(DO_Mode_e mode);
	void setLevel(DO_Channel_e channel, DO_Level_e level);

private:
	DO_Mode_e mode;
    MCP23017PI* expander[2];

	DigitalOut();

};

#endif // DIGITALOUT_H
