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

#ifndef NONEGAMEPAD_H
#define NONEGAMEPAD_H

#include <stdint.h>
#include "InputDevice.h"

class NONEGamepad : public InputDevice {
  public:
    NONEGamepad();
    ~NONEGamepad();

    virtual void initialize(InputDevice::Channel_e channel);
    virtual void update();

  private:
    InputDevice::Channel_e channel;
    uint32_t uinp_fd;
};

#endif
