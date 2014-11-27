#include "PowerSwitch.h"

PowerSwitch::PowerSwitch()
{
	setPowerSignal(PowerSwitch::STATE_ON);
}

PowerSwitch::~PowerSwitch()
{
}

void PowerSwitch::setPowerSignal(PowerState_e state)
{
	if (state == STATE_OFF) {
		DigitalOut::getInstance().setLevel(DigitalOut::DO_CHANNEL_TOPOWERSWITCH, DigitalOut::DO_LEVEL_LOW);
	} else {
		DigitalOut::getInstance().setLevel(DigitalOut::DO_CHANNEL_TOPOWERSWITCH, DigitalOut::DO_LEVEL_HIGH);
	}
}

PowerSwitch::ShutdownSignal_e PowerSwitch::getShutdownSignal()
{
	ShutdownSignal_e signal = SHUTDOWN_FALSE;
	if (DigitalIn::getInstance().getLevel(DigitalIn::DI_CHANNEL_FROMPOWERSWITCH) == DigitalIn::DI_LEVEL_LOW) {
		signal = SHUTDOWN_FALSE;
	} else {
		signal = SHUTDOWN_TRUE;
	}
	return signal;
}
