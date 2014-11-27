#ifndef DIGITALIN_H
#define DIGITALIN_H

class DigitalIn
{
public:
	typedef enum {
	    DI_CHANNEL_FROMPOWERSWITCH = 0,
	    DI_CHANNEL_P1_RIGHT,
	    DI_CHANNEL_P1_LEFT,
	    DI_CHANNEL_P1_UP,
	    DI_CHANNEL_P1_DOWN,
	    DI_CHANNEL_P1_SW1,
	    DI_CHANNEL_P1_SW2,
	    DI_CHANNEL_P1_SW3,
	    DI_CHANNEL_P1_SW4,
	    DI_CHANNEL_P1_SW5,
	    DI_CHANNEL_P1_SW6,
	    DI_CHANNEL_P1_SW7,
	    DI_CHANNEL_P1_SW8,
	    DI_CHANNEL_P1_START,
	    DI_CHANNEL_P1_COIN,
	    DI_CHANNEL_P1_A,
	    DI_CHANNEL_P1_B,
	    DI_CHANNEL_P2_RIGHT,
	    DI_CHANNEL_P2_LEFT,
	    DI_CHANNEL_P2_UP,
	    DI_CHANNEL_P2_DOWN,
	    DI_CHANNEL_P2_SW1,
	    DI_CHANNEL_P2_SW2,
	    DI_CHANNEL_P2_SW3,
	    DI_CHANNEL_P2_SW4,
	    DI_CHANNEL_P2_SW5,
	    DI_CHANNEL_P2_SW6,
	    DI_CHANNEL_P2_SW7,
	    DI_CHANNEL_P2_SW8,
	    DI_CHANNEL_P2_START,
	    DI_CHANNEL_P2_COIN,
	    DI_CHANNEL_P2_A,
	    DI_CHANNEL_P2_B
	} DI_Channel_e;

	typedef enum {
	    DI_LEVEL_LOW = 0,
	    DI_LEVEL_HIGH
	} DI_Level_e;

	~DigitalIn();

	static DigitalIn& getInstance() {
		static DigitalIn digitalIn = DigitalIn();
		return digitalIn;
	}

	void updateLevels();
	DI_Level_e getLevel(DI_Channel_e channel);

private:
	DigitalIn();

};

#endif // DIGITALIN_H
