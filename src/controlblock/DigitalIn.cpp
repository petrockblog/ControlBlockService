#include <stdint.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include "DigitalIn.h"

constexpr uint32_t MCPBASE1 = 100;
constexpr uint32_t MCPBASE2 = 116;


DigitalIn::DigitalIn() {
	wiringPiSetup ();
	mcp23017Setup (MCPBASE1, 0x20);
	mcp23017Setup (MCPBASE2, 0x27);	

	pinMode(1, INPUT);
	for (int32_t i = 0 ; i < 16 ; ++i) {
		pinMode (MCPBASE1 + i, INPUT);
		pinMode (MCPBASE2 + i, INPUT);
		pullUpDnControl (MCPBASE1 + i, PUD_UP);
		pullUpDnControl (MCPBASE2 + i, PUD_UP);
	}	
}

DigitalIn::~DigitalIn() {
}

DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel) {
	DI_Level_e returnLevel = DI_LEVEL_LOW;

	switch (channel) {
		case DI_CHANNEL_FROMPOWERSWITCH:
			returnLevel = digitalRead(1) == LOW ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_RIGHT:
			returnLevel = digitalRead(MCPBASE1 + 0) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_LEFT:
			returnLevel = digitalRead(MCPBASE1 + 1) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_UP:
			returnLevel = digitalRead(MCPBASE1 + 2) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_DOWN:
			returnLevel = digitalRead(MCPBASE1 + 3) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW1:
			returnLevel = digitalRead(MCPBASE1 + 4) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW2:
			returnLevel = digitalRead(MCPBASE1 + 5) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW3:
			returnLevel = digitalRead(MCPBASE1 + 6) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW4:
			returnLevel = digitalRead(MCPBASE1 + 7) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW5:
			returnLevel = digitalRead(MCPBASE2 + 0) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW6:
			returnLevel = digitalRead(MCPBASE2 + 1) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW7:
			returnLevel = digitalRead(MCPBASE2 + 2) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_SW8:
			returnLevel = digitalRead(MCPBASE2 + 3) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_START:
			returnLevel = digitalRead(MCPBASE2 + 4) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_COIN:
			returnLevel = digitalRead(MCPBASE2 + 5) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_A:
			returnLevel = digitalRead(MCPBASE2 + 6) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P1_B:
			returnLevel = digitalRead(MCPBASE2 + 7) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_RIGHT:
			returnLevel = digitalRead(MCPBASE1 + 15) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_LEFT:
			returnLevel = digitalRead(MCPBASE1 + 14) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_UP:
			returnLevel = digitalRead(MCPBASE1 + 13) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_DOWN:
			returnLevel = digitalRead(MCPBASE1 + 12) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW1:
			returnLevel = digitalRead(MCPBASE1 + 11) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW2:
			returnLevel = digitalRead(MCPBASE1 + 10) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW3:
			returnLevel = digitalRead(MCPBASE1 + 9) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW4:
			returnLevel = digitalRead(MCPBASE1 + 8) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW5:
			returnLevel = digitalRead(MCPBASE2 + 15) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW6:
			returnLevel = digitalRead(MCPBASE2 + 14) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW7:
			returnLevel = digitalRead(MCPBASE2 + 13) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_SW8:
			returnLevel = digitalRead(MCPBASE2 + 12) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_START:
			returnLevel = digitalRead(MCPBASE2 + 11) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_COIN:
			returnLevel = digitalRead(MCPBASE2 + 10) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_A:
			returnLevel = digitalRead(MCPBASE2 + 9) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
		case DI_CHANNEL_P2_B:
			returnLevel = digitalRead(MCPBASE2 + 8) == HIGH ? DI_LEVEL_LOW : DI_LEVEL_HIGH;
			break;
	}
	return returnLevel;
}

void DigitalIn::updateLevels() {
}
