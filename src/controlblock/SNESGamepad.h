/*
 * (c) Copyright 2014  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlockService
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#ifndef SNESGAMEPAD_H
#define SNESGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"

class SNESGamepad : public InputDevice {
  public:
    /* bit masks for checking the button states for SNES controllers */
    static const uint16_t GPAD_SNES_B = 0x01;
    static const uint16_t GPAD_SNES_Y = 0x02;
    static const uint16_t GPAD_SNES_SELECT = 0x04;
    static const uint16_t GPAD_SNES_START = 0x08;
    static const uint16_t GPAD_SNES_UP = 0x10;
    static const uint16_t GPAD_SNES_DOWN = 0x20;
    static const uint16_t GPAD_SNES_LEFT = 0x40;
    static const uint16_t GPAD_SNES_RIGHT = 0x80;
    static const uint16_t GPAD_SNES_A = 0x100;
    static const uint16_t GPAD_SNES_X = 0x200;
    static const uint16_t GPAD_SNES_L = 0x400;
    static const uint16_t GPAD_SNES_R = 0x800;

    /* bit masks for checking the button states for NES controllers */
    static const uint16_t GPAD_NES_B = 0x01;
    static const uint16_t GPAD_NES_SELECT = 0x04;
    static const uint16_t GPAD_NES_START = 0x08;
    static const uint16_t GPAD_NES_UP = 0x10;
    static const uint16_t GPAD_NES_DOWN = 0x20;
    static const uint16_t GPAD_NES_LEFT = 0x40;
    static const uint16_t GPAD_NES_RIGHT = 0x80;
    static const uint16_t GPAD_NES_A = 0x100;

    SNESGamepad();
    ~SNESGamepad();

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

  private:
    const uint16_t PIN_P1_VCC = 115;
    const uint16_t PIN_P2_VCC = 114;
    const uint16_t PIN_P1P2_LATCH = 113;
    const uint16_t PIN_P1P2_CLOCK = 112;
    const uint16_t PIN_P1_DATA = 111;
    const uint16_t PIN_P2_DATA = 110;

    InputDevice::Channel_e channel;
    uint32_t uinp_fd;
    static uint16_t state1;
    static uint16_t state2;

    uint16_t getSNESControllerState();
};

#endif
