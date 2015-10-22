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

#include "ControlBlock.h"
#include <iostream>
#include <map>
#include "ArcadeGamepad.h"
#include "SNESGamepad.h"
#include "MAMEGamepad.h"
#include "NONEGamepad.h"

ControlBlock::ControlBlock() : configuration(new ControlBlockConfiguration()) {
    std::map<ControlBlockConfiguration::ShutdownType_e,
             PowerSwitch::ShutdownActivated_e> switchMapping;
    switchMapping[ControlBlockConfiguration::SHUTDOWN_ACTIVATED] =
        PowerSwitch::SHUTDOWN_ACTIVATED;
    switchMapping[ControlBlockConfiguration::SHUTDOWN_DEACTIVATED] =
        PowerSwitch::SHUTDOWN_DEACTIVATED;

    configuration->initialize();

    numGamepads = MAXNUMGAMEPADS;
    if (configuration->getSingleGamepad() == 
        ControlBlockConfiguration::SINGLE_GAMEPAD_ACTIVATED) {
        numGamepads = 1;
    } 

    powerSwitch =
        new PowerSwitch(switchMapping[configuration->getShutdownActivation()]);

    for (uint8_t counter = 0; counter < numGamepads; counter++) {
        if (configuration->getGamepadType() ==
            ControlBlockConfiguration::GAMEPAD_ARCADE) {
            gamepads[counter] = new ArcadeGamepad();
        } else if (configuration->getGamepadType() ==
                   ControlBlockConfiguration::GAMEPAD_SNES) {
            gamepads[counter] = new SNESGamepad();
        } else if (configuration->getGamepadType() ==
                   ControlBlockConfiguration::GAMEPAD_MAME) {
            gamepads[counter] = new MAMEGamepad();
        } else {
            gamepads[counter] = new NONEGamepad();
        }
        gamepads[counter]->initialize(counter == 0 ? InputDevice::CHANNEL_1
                                                   : InputDevice::CHANNEL_2);
    }
}

ControlBlock::~ControlBlock() {
    for (uint8_t counter = 0; counter < numGamepads; counter++) {
        delete gamepads[counter];
        gamepads[counter] = 0;
    }
    delete powerSwitch;
    delete configuration;
}

void ControlBlock::update() {
    try {
        for (uint8_t counter = 0; counter < numGamepads; counter++) {
            gamepads[counter]->update();
        }
    } catch(int errno) {
        std::cout << "Error while updating the gamepad devices. Error number: "
                  << errno << std::endl;
    }
    try {
        powerSwitch->update();
    } catch(int errno) {
        std::cout
            << "Error while updating the power switch instance. Error number: "
            << errno << std::endl;
    }
}
