#include <stdlib.h>
#include "PowerSwitch.h"
#include "GPIO.h"

PowerSwitch::PowerSwitch(ShutdownActivated_e doShutdown) : doShutdown(SHUTDOWN_ACTIVATED) {
	// RPI_STATUS signal
	GPIO::getInstance().setDirection(PIN_RPI_STATUS, GPIO::DIRECTION_OUT);

	// RPI_SHUTDOWN signal
	GPIO::getInstance().setDirection(PIN_RPI_SHUTDOWN, GPIO::DIRECTION_IN);
	GPIO::getInstance().setPullupMode(PIN_RPI_SHUTDOWN, GPIO::PULLDOWN_ENABLED);

	setPowerSignal(PowerSwitch::STATE_ON);
}

PowerSwitch::~PowerSwitch() {
}

void PowerSwitch::update() {
	static bool isShutdownInitiated = false;
	
	if ((doShutdown == SHUTDOWN_ACTIVATED) && 
		(getShutdownSignal() == SHUTDOWN_TRUE) && 
		(isShutdownInitiated == false)) 
	{
		system("shutdown -t 3 -h now");
		isShutdownInitiated = true;
	}	
}

void PowerSwitch::setPowerSignal(PowerState_e state) {
	if (state == STATE_OFF) {
		GPIO::getInstance().write(PIN_RPI_STATUS, GPIO::LEVEL_LOW);
	} else {
		GPIO::getInstance().write(PIN_RPI_STATUS, GPIO::LEVEL_HIGH);
	}
}

PowerSwitch::ShutdownSignal_e PowerSwitch::getShutdownSignal() {
	ShutdownSignal_e signal = SHUTDOWN_FALSE;
	if (GPIO::getInstance().read(PIN_RPI_SHUTDOWN) == GPIO::LEVEL_LOW) {
		signal = SHUTDOWN_FALSE;
	} else {
		signal = SHUTDOWN_TRUE;
	}
	return signal;
}
