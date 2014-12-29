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

#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <linux/uinput.h>

#include "uinputcpp.h"
#include "ArcadeGamepad.h"
#include "GPIO.h"

ArcadeGamepad::ArcadeGamepad()
    : channel(InputDevice::CHANNEL_UNDEFINED), uinp_fd(0) {}

ArcadeGamepad::~ArcadeGamepad() { UInputcpp::releaseHandle(uinp_fd); }

void ArcadeGamepad::initialize(InputDevice::Channel_e channel) {
    uinp_fd = UInputcpp::getHandle();
    this->channel = channel;

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock Arcade Gamepad",
            strlen("ControlBlock Arcade Gamepad"));
    uinp.id.version = 4;
    uinp.id.bustype = BUS_USB;
    uinp.id.product = 1;
    uinp.id.vendor = 1;

    // Setup the uinput device
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_REL);

    // gamepad, buttons
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_A);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_B);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_C);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_X);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Y);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Z);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL2);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR2);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_START);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_SELECT);

    // gamepad, directions
    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_Y);
    uinp.absmin[ABS_X] = 0;
    uinp.absmax[ABS_X] = 4;
    uinp.absmin[ABS_Y] = 0;
    uinp.absmax[ABS_Y] = 4;

    /* Create input device into input sub-system */
    write(uinp_fd, &uinp, sizeof(uinp));
    if (ioctl(uinp_fd, UI_DEV_CREATE)) {
        printf("[ArcadeGamepad] Unable to create UINPUT device.");
        throw - 1;
    }

    UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
    UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);

    GPIO &gpio = GPIO::getInstance();
    for (int32_t i = 0; i < 16; ++i) {
        gpio.setDirection(100 + i, GPIO::DIRECTION_IN);
        gpio.setDirection(200 + i, GPIO::DIRECTION_IN);
        gpio.setPullupMode(100 + i, GPIO::PULLUP_ENABLED);
        gpio.setPullupMode(200 + i, GPIO::PULLUP_ENABLED);
    }
}

void ArcadeGamepad::update() {
    GPIO &gpio = GPIO::getInstance();

    if (channel == InputDevice::CHANNEL_1) {
        // axes
        if (gpio.read(101) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
        } else if (gpio.read(100) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
        } else {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
        }
        if (gpio.read(102) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
        } else if (gpio.read(103) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
        } else {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
        }

        // buttons
        UInputcpp::setKeyState(
            uinp_fd, BTN_A, gpio.read(104) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_B, gpio.read(105) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_C, gpio.read(106) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_X, gpio.read(107) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_Y, gpio.read(200) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_Z, gpio.read(201) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_TL, gpio.read(202) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_TR, gpio.read(203) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_START,
                               gpio.read(204) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_SELECT,
                               gpio.read(205) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_TL2,
                               gpio.read(206) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_TR2,
                               gpio.read(207) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
    } else if (channel == InputDevice::CHANNEL_2) {
        // axes
        if (gpio.read(114) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
        } else if (gpio.read(115) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
        } else {
            UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
        }
        if (gpio.read(113) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
        } else if (gpio.read(112) == GPIO::LEVEL_LOW) {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
        } else {
            UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
        }

        // buttons
        UInputcpp::setKeyState(
            uinp_fd, BTN_A, gpio.read(111) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_B, gpio.read(110) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_C, gpio.read(109) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_X, gpio.read(108) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_Y, gpio.read(215) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_Z, gpio.read(214) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_TL, gpio.read(213) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(
            uinp_fd, BTN_TR, gpio.read(212) == GPIO::LEVEL_LOW ? 1 : 0, EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_START,
                               gpio.read(211) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_SELECT,
                               gpio.read(210) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_TL2,
                               gpio.read(209) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
        UInputcpp::setKeyState(uinp_fd, BTN_TR2,
                               gpio.read(208) == GPIO::LEVEL_LOW ? 1 : 0,
                               EV_KEY);
    } else {
        std::cout << "ArcadeGamepad.cpp. Error." << std::endl;
        throw 3;
    }
}
