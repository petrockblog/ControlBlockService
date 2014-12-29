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

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "ControlBlockConfiguration.h"

ControlBlockConfiguration::ControlBlockConfiguration()
    : gamepadType(GAMEPAD_ARCADE), doShutdown(SHUTDOWN_ACTIVATED) {}

ControlBlockConfiguration::~ControlBlockConfiguration() {}

void ControlBlockConfiguration::initialize() {
    try {
        Json::Value root;
        Json::Reader reader;

        std::ifstream t("/etc/controlblockconfig.cfg");
        std::string config_doc((std::istreambuf_iterator<char>(t)),
                               std::istreambuf_iterator<char>());

        bool parsingSuccessful = reader.parse(config_doc, root);
        if (!parsingSuccessful) {
            std::cout << "[ControlBlock] Failed to parse configuration\n"
                      << reader.getFormattedErrorMessages();
            return;
        }

        std::string configvalue = root["input"]["gamepadtype"].asString();
        if (configvalue.compare("arcade") == 0) {
            gamepadType = GAMEPAD_ARCADE;
            std::cout << "[ControlBlock] Gamepadtype = ARCADE gamepads"
                      << std::endl;
        } else if (configvalue.compare("mame") == 0) {
            gamepadType = GAMEPAD_MAME;
            std::cout << "[ControlBlock] Gamepadtype = MAME Keyboard"
                      << std::endl;
        } else if (configvalue.compare("snes") == 0) {
            gamepadType = GAMEPAD_SNES;
            std::cout << "[ControlBlock] Gamepadtype = SNES gamepads"
                      << std::endl;
        } else {
            gamepadType = GAMEPAD_NONE;
            std::cout << "[ControlBlock] Gamepadtype = NONE" << std::endl;
        }

        bool configboolean = root["powerswitch"]["activated"].asBool();
        if (configboolean) {
            doShutdown = SHUTDOWN_ACTIVATED;
            std::cout << "[ControlBlock] Shutdown is ACTIVATED" << std::endl;
        } else {
            doShutdown = SHUTDOWN_DEACTIVATED;
            std::cout << "[ControlBlock] Shutdown is DEACTIVATED" << std::endl;
        }
    } catch(int errno) {
        std::cout << "[ControlBlock] Error while initializing "
                     "ControlBlockConfiguration instance. Error number: "
                  << errno << std::endl;
    }
}

ControlBlockConfiguration::GamepadType_e
ControlBlockConfiguration::getGamepadType() const {
    return gamepadType;
}

ControlBlockConfiguration::ShutdownType_e
ControlBlockConfiguration::getShutdownActivation() const {
    return doShutdown;
}
