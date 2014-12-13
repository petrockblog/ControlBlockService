#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"
#include "mcp23017pi.h"

class GPIO {

public:
	typedef enum {
		LEVEL_LOW = 0,
		LEVEL_HIGH,
		LEVEL_UNAVAILABLE
	} Level_e;

	typedef enum {
		DIRECTION_IN = 0,
		DIRECTION_OUT
	} Direction_e;

	typedef enum {
		PULLUP_ENABLED = 0,
		PULLDOWN_ENABLED,
		PULLUPDOWN_DISABLED
	} PullupMode_e;

	virtual ~GPIO();

	static GPIO& getInstance() {
		static GPIO instance = GPIO();
		return instance;
	}

	void setDirection(uint16_t pin, Direction_e direction);
	void setPullupMode(uint16_t pin, PullupMode_e mode);
	Level_e read(uint16_t pin);
	void write(uint16_t pin, Level_e level);

private:
	static bool isBCM2835Initialized;
	MCP23017PI expander1;
	MCP23017PI expander2;

	GPIO();

};

#endif
