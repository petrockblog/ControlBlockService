#include <stdint.h>

#include "mcp23017pi.h"
#include "DigitalIn.h"

DigitalIn::DigitalIn() : mode(DI_MODE_ALLIN) {
	expander[0] = new MCP23017PI(0);
	expander[1] = new MCP23017PI(7);
	expander[0]->begin();
	expander[1]->begin();
	setMode(mode);
}

DigitalIn::~DigitalIn() {
	expander[0]->end();
	expander[1]->end();
	delete expander[1];
	delete expander[0];
}

void DigitalIn::setMode(DI_Mode_e mode) {
	this->mode = mode;

	switch (mode) {
		case DI_MODE_ALLIN:
			bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
			for (int32_t i = 0 ; i < 16 ; ++i) {
				expander[0]->setPinMode (i, MCP23017PI::DIR_INPUT);
				expander[1]->setPinMode (i, MCP23017PI::DIR_INPUT);
				expander[0]->setPullupMode(i, MCP23017PI::PULLUP_ENABLED);
				expander[1]->setPullupMode(i, MCP23017PI::PULLUP_ENABLED);
			}	
			break;
		case DI_MODE_SNES:
			bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_INPT);
			for (int32_t i = 0 ; i < 16 ; ++i) {
				if ((i != 0) && (i != 1) && (i != 2) && (i != 13) && (i != 14) && (i != 15)) {
					expander[0]->setPinMode (i, MCP23017PI::DIR_INPUT);
					expander[0]->setPullupMode(i, MCP23017PI::PULLUP_ENABLED);
				}
				expander[1]->setPinMode (i, MCP23017PI::DIR_INPUT);
				expander[1]->setPullupMode(i, MCP23017PI::PULLUP_ENABLED);
			}
			break;
		default:
			throw 50;
	}
}

// returns LOGICAL high or low
DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel) {
	DI_Level_e returnLevel = DI_LEVEL_LOW;

	switch (channel) {
		case DI_CHANNEL_FROMPOWERSWITCH:
			returnLevel = bcm2835_gpio_lev(RPI_GPIO_P1_12) == LOW ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_RIGHT:
			returnLevel = expander[0]->digitalRead(0) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_LEFT:
			returnLevel = expander[0]->digitalRead(1) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_UP:
			returnLevel = expander[0]->digitalRead(2) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_DOWN:
			returnLevel = expander[0]->digitalRead(3) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW1:
			returnLevel = expander[0]->digitalRead(4) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW2:
			returnLevel = expander[0]->digitalRead(5) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW3:
			returnLevel = expander[0]->digitalRead(6) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW4:
			returnLevel = expander[0]->digitalRead(7) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW5:
			returnLevel = expander[1]->digitalRead(0) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW6:
			returnLevel = expander[1]->digitalRead(1) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW7:
			returnLevel = expander[1]->digitalRead(2) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW8:
			returnLevel = expander[1]->digitalRead(3) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_START:
			returnLevel = expander[1]->digitalRead(4) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_COIN:
			returnLevel = expander[1]->digitalRead(5) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_A:
			returnLevel = expander[1]->digitalRead(6) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_B:
			returnLevel = expander[1]->digitalRead(7) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_RIGHT:
			returnLevel = expander[0]->digitalRead(15) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_LEFT:
			returnLevel = expander[0]->digitalRead(14) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_UP:
			returnLevel = expander[0]->digitalRead(13) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_DOWN:
			returnLevel = expander[0]->digitalRead(12) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW1:
			returnLevel = expander[0]->digitalRead(11) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW2:
			returnLevel = expander[0]->digitalRead(10) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW3:
			returnLevel = expander[0]->digitalRead(9) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW4:
			returnLevel = expander[0]->digitalRead(8) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW5:
			returnLevel = expander[1]->digitalRead(15) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW6:
			returnLevel = expander[1]->digitalRead(14) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW7:
			returnLevel = expander[1]->digitalRead(13) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW8:
			returnLevel = expander[1]->digitalRead(12) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_START:
			returnLevel = expander[1]->digitalRead(11) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_COIN:
			returnLevel = expander[1]->digitalRead(10) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_A:
			returnLevel = expander[1]->digitalRead(9) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_B:
			returnLevel = expander[1]->digitalRead(8) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_DATA:
			returnLevel = expander[0]->digitalRead(3) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_DATA:
			returnLevel = expander[0]->digitalRead(12) == MCP23017PI::LEVEL_HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
	}
	return returnLevel;
}

void DigitalIn::updateLevels() {
}
