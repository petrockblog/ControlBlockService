#include "DigitalIn.h"

DigitalIn::DigitalIn()
{
}

DigitalIn::~DigitalIn()
{
}

DigitalIn::DI_Level_e DigitalIn::getLevel(DigitalIn::DI_Channel_e channel)
{
	DI_Level_e returnLevel = DI_LEVEL_LOW;
	return returnLevel;
}

void DigitalIn::updateLevels()
{
}
