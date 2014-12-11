#include "../../controlblock/mcp23017pi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    uint16_t state;
    MCP23017PI mcp1(0);
    MCP23017PI mcp2(7);

    mcp1.begin();
    mcp2.begin();

    for (uint8_t i = 0; i < 15; i++) {
        mcp1.pinMode(i, MCP23017PI::DIR_OUTPUT);
        mcp2.pinMode(i, MCP23017PI::DIR_OUTPUT);
    }
    mcp1.pinMode(15, MCP23017PI::DIR_INPUT);
    mcp1.pullupMode(15, MCP23017PI::PULLUP_ENABLED);
    mcp2.pinMode(15, MCP23017PI::DIR_INPUT);
    mcp2.pullupMode(15, MCP23017PI::PULLUP_ENABLED);

    for (int i = 0; i < 6000000; i++) {
        mcp1.writeGPIO(0xFFFF);
        mcp2.writeGPIO(0xFFFF);
        delayMicroseconds(1);
        mcp1.writeGPIO(0x0000);
        mcp2.writeGPIO(0x0000);
        delayMicroseconds(1);
        state = mcp1.readGPIO();
        state = mcp2.readGPIO();
    }

    mcp1.end();
    mcp2.end();

    return 0;
}