/*
 * q2w.c:
 *      Using the Quick 2 wire board for its mcp23017
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 */

#include <stdio.h>
#include <wiringPi.h>
#include <mcp23017.h>

#define MCPBASE1 100
#define MCPBASE2 116

int main (void)
{
  int i;

  wiringPiSetup ();
  mcp23017Setup (MCPBASE1, 0x20);
  mcp23017Setup (MCPBASE2, 0x27);

  printf ("Raspberry Pi - MCP23017 Test\n");

  for (i = 0 ; i < 16 ; ++i) {
    pinMode (MCPBASE1 + i, INPUT);
    pinMode (MCPBASE2 + i, INPUT);
    pullUpDnControl (MCPBASE1 + i, PUD_UP);
    pullUpDnControl (MCPBASE2 + i, PUD_UP);
  }

  while (1) {
    for (i = 0; i < 16; ++i) {
      if (digitalRead (MCPBASE1 + i) == 0) {
        printf("Pressed button %d of player 1\n",i);
      }
      if (digitalRead (MCPBASE2 + i) == 0) {
        printf("Pressed button %d of player 2\n",i);
      }
    }
    delay(500);
  }
  
  return 0 ;
}
