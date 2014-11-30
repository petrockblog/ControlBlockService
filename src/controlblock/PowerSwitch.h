#ifndef POWERSWITCH_H
#define POWERSWITCH_H

#include "DigitalOut.h"
#include "DigitalIn.h"

class PowerSwitch {
public:
	typedef enum {
	    STATE_OFF = 0,
	    STATE_ON
	} PowerState_e;

	typedef enum {
	    SHUTDOWN_TRUE = 0,
	    SHUTDOWN_FALSE
	} ShutdownSignal_e;

	typedef enum {
		SHUTDOWN_ACTIVATED = 0,
		SHUTDOWN_DEACTIVATED
	} ShutdownActivated_e;

	PowerSwitch(ShutdownActivated_e doShutdown);
	~PowerSwitch();

	void update();

private:
	ShutdownActivated_e doShutdown;

	void setPowerSignal(PowerState_e state);
	ShutdownSignal_e getShutdownSignal();

};

#endif // POWERSWITCH_H
