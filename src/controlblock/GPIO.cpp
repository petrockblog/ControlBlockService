#include "GPIO.h"
#include <iostream>
#include "bcm2835.h"

bool GPIO::isBCM2835Initialized = false;

GPIO::GPIO() : expander1(MCP23017PI(0)), expander2(MCP23017PI(7)) {
	if (!isBCM2835Initialized)
	{
		if(!bcm2835_init()) {
			std::cout << "Error initializing GPIO." << std::endl;
		}
		// bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626);
		bcm2835_i2c_setClockDivider(160); // 250MHz / 160 = 1,5625 Mhz Clock Rate for I2C
		#ifdef DEBUG		
			std::cout << "Setting clock divider to " << int(BCM2835_I2C_CLOCK_DIVIDER_626) << std::endl;
		#endif
	}

	expander1.begin();
	expander2.begin();	
}

GPIO::~GPIO() {
	#ifdef DEBUG		
		std::cout << "GPIO: Destructor called." << std::endl;
	#endif		
	expander1.end();
	expander2.end();	
	bcm2835_close();
	isBCM2835Initialized = false;
}

void GPIO::setDirection(uint16_t pin, Direction_e direction) {
	if (pin < 100) {
		if (direction == DIRECTION_OUT) {
			bcm2835_gpio_fsel((uint8_t)pin, BCM2835_GPIO_FSEL_OUTP);
		} else if (direction==DIRECTION_IN) {		
			bcm2835_gpio_fsel((uint8_t)pin, BCM2835_GPIO_FSEL_INPT);
		}
	} else if (pin < 200) {
		if (direction == DIRECTION_IN ) {
			expander1.setPinMode(pin-100, MCP23017PI::DIR_INPUT);
		} else {
			expander1.setPinMode(pin-100, MCP23017PI::DIR_OUTPUT);
		}
	} else if (pin < 300) {
		if (direction == DIRECTION_IN ) {
			expander2.setPinMode(pin-200, MCP23017PI::DIR_INPUT);
		} else {
			expander2.setPinMode(pin-200, MCP23017PI::DIR_OUTPUT);
		}
	} else {
		std::cout << "setDirection: Unknown pin number." << std::endl;
	}
}

void GPIO::setPullupMode(uint16_t pin, PullupMode_e mode) {
	if (pin < 100) {
		if (mode == PULLUP_ENABLED) {
			bcm2835_gpio_set_pud((uint8_t)pin, BCM2835_GPIO_PUD_UP);
		} else {
			bcm2835_gpio_set_pud((uint8_t)pin, BCM2835_GPIO_PUD_OFF);
		}
	} else if (pin < 200) {
		if (mode == PULLUP_ENABLED) {
			expander1.setPullupMode(pin - 100, MCP23017PI::PULLUP_ENABLED);
		} else {
			expander1.setPullupMode(pin - 100, MCP23017PI::PULLUP_DISABLED);
		}
	} else if (pin < 300) {
		if (mode == PULLUP_ENABLED) {
			expander2.setPullupMode(pin - 200, MCP23017PI::PULLUP_ENABLED);
		} else {
			expander2.setPullupMode(pin - 200, MCP23017PI::PULLUP_DISABLED);
		}
	}	
}

GPIO::Level_e GPIO::read(uint16_t pin) {
	if (pin < 100) {
		return (bcm2835_gpio_lev((uint8_t)pin) == HIGH) ? LEVEL_HIGH : LEVEL_LOW;
	} else if (pin < 200) {
		return (expander1.digitalRead(pin - 100) == MCP23017PI::LEVEL_HIGH) ? LEVEL_HIGH : LEVEL_LOW;
	} else if (pin < 300) {
		return (expander2.digitalRead(pin - 200) == MCP23017PI::LEVEL_HIGH) ? LEVEL_HIGH : LEVEL_LOW;
	} else {
		return LEVEL_UNAVAILABLE;
	}
}

void GPIO::write(uint16_t pin, GPIO::Level_e level) {
	if (pin < 100) {
		bcm2835_gpio_write((uint8_t)pin, level == LEVEL_LOW ? LOW : HIGH);
	} else if (pin < 200) {
		expander1.digitalWrite(pin - 100, level == LEVEL_LOW ? MCP23017PI::LEVEL_LOW : MCP23017PI::LEVEL_HIGH);
	} else if (pin < 300) {
		expander2.digitalWrite(pin - 200, level == LEVEL_LOW ? MCP23017PI::LEVEL_LOW : MCP23017PI::LEVEL_HIGH);
	}
}
