#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "DigitalOut.h"
#include "DigitalIn.h"

class PowerSwitch
{
public:

	typedef enum {
	    STATE_OFF = 0,
	    STATE_ON
	} PowerState_e;

	typedef enum {
	    SHUTDOWN_TRUE = 0,
	    SHUTDOWN_FALSE
	} ShutdownSignal_e;

	PowerSwitch();
	~PowerSwitch();

	void setPowerSignal(PowerState_e state);
	ShutdownSignal_e getShutdownSignal();

private:

};

#endif // POWERSWITCH_H
