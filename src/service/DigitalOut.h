#ifndef DIGITALOUT_H
#define DIGITALOUT_H

class DigitalOut
{
public:

	typedef enum {
	    DO_CHANNEL_TOPOWERSWITCH = 0
	} DO_Channel_e;

	typedef enum {
	    DO_LEVEL_LOW = 0,
	    DO_LEVEL_HIGH
	} DO_Level_e;

	~DigitalOut();

	static DigitalOut& getInstance() {
		static DigitalOut digitalOut = DigitalOut();
		return digitalOut;
	}

	void setLevel(DO_Channel_e channel, DO_Level_e level);

private:
	DigitalOut();

};

#endif // DIGITALOUT_H
