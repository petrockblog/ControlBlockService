#include "ControlBlock.h"

ControlBlock::ControlBlock() : powerSwitch(PowerSwitch())
{
	for (uint8_t counter = 0; counter<NUMGAMEPADS; counter++) {
		gamepads[counter] = new UInputGamepad();
	}
}

ControlBlock::~ControlBlock()
{
	for (uint8_t counter = 0; counter<NUMGAMEPADS; counter++) {
		delete gamepads[counter];
		gamepads[counter] = 0;
	}
}

void ControlBlock::updateGamepads()
{
	DigitalIn di = DigitalIn::getInstance();
	// axes
	gamepads[0]->setKeyState(ABS_X, di.getLevel(DigitalIn::DI_CHANNEL_P1_LEFT) == DigitalIn::DI_LEVEL_LOW ? 2 : 0, EV_ABS);
	gamepads[0]->setKeyState(ABS_X, di.getLevel(DigitalIn::DI_CHANNEL_P1_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 2 : 4, EV_ABS);
	gamepads[0]->setKeyState(ABS_Y, di.getLevel(DigitalIn::DI_CHANNEL_P1_UP) == DigitalIn::DI_LEVEL_LOW ? 2 : 0, EV_ABS);
	gamepads[0]->setKeyState(ABS_Y, di.getLevel(DigitalIn::DI_CHANNEL_P1_DOWN) == DigitalIn::DI_LEVEL_LOW ? 2 : 4, EV_ABS);

	// buttons
	gamepads[0]->setKeyState(BTN_A, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_B, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_C, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_X, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_Y, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_Z, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_TL, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_TR, di.getLevel(DigitalIn::DI_CHANNEL_P1_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_START, di.getLevel(DigitalIn::DI_CHANNEL_P1_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[0]->setKeyState(BTN_SELECT, di.getLevel(DigitalIn::DI_CHANNEL_P1_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

	// axes
	gamepads[1]->setKeyState(ABS_X, di.getLevel(DigitalIn::DI_CHANNEL_P2_LEFT) == DigitalIn::DI_LEVEL_LOW ? 2 : 0, EV_ABS);
	gamepads[1]->setKeyState(ABS_X, di.getLevel(DigitalIn::DI_CHANNEL_P2_RIGHT) == DigitalIn::DI_LEVEL_LOW ? 2 : 4, EV_ABS);
	gamepads[1]->setKeyState(ABS_Y, di.getLevel(DigitalIn::DI_CHANNEL_P2_UP) == DigitalIn::DI_LEVEL_LOW ? 2 : 0, EV_ABS);
	gamepads[1]->setKeyState(ABS_Y, di.getLevel(DigitalIn::DI_CHANNEL_P2_DOWN) == DigitalIn::DI_LEVEL_LOW ? 2 : 4, EV_ABS);

	// buttons
	gamepads[1]->setKeyState(BTN_A, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW1) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_B, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW2) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_C, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW3) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_X, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW4) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_Y, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW5) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_Z, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW6) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_TL, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW7) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_TR, di.getLevel(DigitalIn::DI_CHANNEL_P2_SW8) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_START, di.getLevel(DigitalIn::DI_CHANNEL_P2_START) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);
	gamepads[1]->setKeyState(BTN_SELECT, di.getLevel(DigitalIn::DI_CHANNEL_P2_COIN) == DigitalIn::DI_LEVEL_LOW ? 0 : 1, EV_KEY);

}

void ControlBlock::updatePowerSwitch()
{
	if (powerSwitch.getShutdownSignal() == PowerSwitch::SHUTDOWN_TRUE) {
		system("shutdown -t 3 -h now");
	}
}