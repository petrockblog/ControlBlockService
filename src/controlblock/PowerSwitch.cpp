#include <stdlib.h>
#include "PowerSwitch.h"

PowerSwitch::PowerSwitch(ShutdownActivated_e doShutdown) : doShutdown(SHUTDOWN_ACTIVATED) {
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
		DigitalOut::getInstance().setLevel(DigitalOut::DO_CHANNEL_TOPOWERSWITCH, DigitalOut::DO_LEVEL_LOW);
	} else {
		DigitalOut::getInstance().setLevel(DigitalOut::DO_CHANNEL_TOPOWERSWITCH, DigitalOut::DO_LEVEL_HIGH);
	}
}

PowerSwitch::ShutdownSignal_e PowerSwitch::getShutdownSignal() {
	ShutdownSignal_e signal = SHUTDOWN_FALSE;
	if (DigitalIn::getInstance().getLevel(DigitalIn::DI_CHANNEL_FROMPOWERSWITCH) == DigitalIn::DI_LEVEL_LOW) {
		signal = SHUTDOWN_FALSE;
	} else {
		signal = SHUTDOWN_TRUE;
	}
	return signal;
}
