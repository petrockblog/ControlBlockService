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

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "config/ControlBlockConfiguration.h"

class InputDevice {
  public:
    typedef enum { CHANNEL_1 = 0, CHANNEL_2, CHANNEL_UNDEFINED } Channel_e;

    InputDevice() {}
    virtual ~InputDevice() {}

    virtual void initialize(Channel_e channel) = 0;
    virtual void update() = 0;
};

#endif
