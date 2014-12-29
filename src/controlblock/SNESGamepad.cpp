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

#include <chrono>
#include <thread>
#include <iostream>
#include <linux/uinput.h>

#include "SNESGamepad.h"
#include "GPIO.h"
#include "uinputcpp.h"

uint16_t SNESGamepad::state1 = 0;
uint16_t SNESGamepad::state2 = 0;

SNESGamepad::SNESGamepad()
    : channel(InputDevice::CHANNEL_UNDEFINED), uinp_fd(0) {}

SNESGamepad::~SNESGamepad() {
    if (uinp_fd != 0) {
        UInputcpp::releaseHandle(uinp_fd);
    }
}

void SNESGamepad::initialize(InputDevice::Channel_e channel) {
    uinp_fd = UInputcpp::getHandle();
    this->channel = channel;

    struct uinput_user_dev uinp;
    memset(&uinp, 0, sizeof(uinp));
    strncpy(uinp.name, "ControlBlock SNES Gamepad",
            strlen("ControlBlock SNES Gamepad"));
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
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_X);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_Y);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR);
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
    }

    UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
    UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);

    GPIO &gpio = GPIO::getInstance();
    if (channel == InputDevice::CHANNEL_1) {
        gpio.setDirection(PIN_P1_VCC, GPIO::DIRECTION_OUT);
        gpio.setDirection(PIN_P1P2_LATCH, GPIO::DIRECTION_OUT);
        gpio.setDirection(PIN_P1P2_CLOCK, GPIO::DIRECTION_OUT);

        gpio.setDirection(PIN_P1_DATA, GPIO::DIRECTION_IN);
        gpio.setPullupMode(PIN_P1_DATA, GPIO::PULLUP_ENABLED);

        gpio.write(PIN_P1_VCC, GPIO::LEVEL_HIGH);
        gpio.write(PIN_P1P2_LATCH, GPIO::LEVEL_LOW);
        gpio.write(PIN_P1P2_CLOCK, GPIO::LEVEL_LOW);
    } else {
        gpio.setDirection(PIN_P2_VCC, GPIO::DIRECTION_OUT);
        gpio.setDirection(PIN_P1P2_LATCH, GPIO::DIRECTION_OUT);
        gpio.setDirection(PIN_P1P2_CLOCK, GPIO::DIRECTION_OUT);

        gpio.setDirection(PIN_P2_DATA, GPIO::DIRECTION_IN);
        gpio.setPullupMode(PIN_P2_DATA, GPIO::PULLUP_ENABLED);

        gpio.write(PIN_P2_VCC, GPIO::LEVEL_HIGH);
        gpio.write(PIN_P1P2_LATCH, GPIO::LEVEL_LOW);
        gpio.write(PIN_P1P2_CLOCK, GPIO::LEVEL_LOW);
    }
}

inline uint16_t SNESGamepad::getSNESControllerState() {
    if (channel == InputDevice::CHANNEL_1) {
        SNESGamepad::state1 = 0;
        SNESGamepad::state2 = 0;
        GPIO &gpio = GPIO::getInstance();

        // latch pulse
        gpio.write(PIN_P1P2_LATCH, GPIO::LEVEL_HIGH);
        gpio.write(PIN_P1P2_LATCH, GPIO::LEVEL_LOW);

        for (uint8_t i = 0; i < 15; i++) {
            GPIO::Level_e level = gpio.read(PIN_P1_DATA);
            if (level == GPIO::LEVEL_LOW) {
                state1 |= (1 << i);
            }
            level = gpio.read(PIN_P2_DATA);
            if (level == GPIO::LEVEL_LOW) {
                state2 |= (1 << i);
            }
            // clock pulse
            gpio.write(PIN_P1P2_CLOCK, GPIO::LEVEL_HIGH);
            gpio.write(PIN_P1P2_CLOCK, GPIO::LEVEL_LOW);
        }
        return state1;
    } else {
        return state2;
    }
}

void SNESGamepad::update() {
    uint16_t state = getSNESControllerState();

    // axes
    if ((state & GPAD_SNES_LEFT) == GPAD_SNES_LEFT) {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 0, EV_ABS);
    } else if ((state & GPAD_SNES_RIGHT) == GPAD_SNES_RIGHT) {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 4, EV_ABS);
    } else {
        UInputcpp::setKeyState(uinp_fd, ABS_X, 2, EV_ABS);
    }
    if ((state & GPAD_SNES_UP) == GPAD_SNES_UP) {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 0, EV_ABS);
    } else if ((state & GPAD_SNES_DOWN) == GPAD_SNES_DOWN) {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 4, EV_ABS);
    } else {
        UInputcpp::setKeyState(uinp_fd, ABS_Y, 2, EV_ABS);
    }

    // buttons
    UInputcpp::setKeyState(
        uinp_fd, BTN_A, (state & GPAD_SNES_A) == GPAD_SNES_A ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_B, (state & GPAD_SNES_B) == GPAD_SNES_B ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_X, (state & GPAD_SNES_X) == GPAD_SNES_X ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_Y, (state & GPAD_SNES_Y) == GPAD_SNES_Y ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_TL, (state & GPAD_SNES_L) == GPAD_SNES_L ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_TR, (state & GPAD_SNES_R) == GPAD_SNES_R ? 1 : 0, EV_KEY);
    UInputcpp::setKeyState(uinp_fd, BTN_START,
                           (state & GPAD_SNES_START) == GPAD_SNES_START ? 1 : 0,
                           EV_KEY);
    UInputcpp::setKeyState(
        uinp_fd, BTN_SELECT,
        (state & GPAD_SNES_SELECT) == GPAD_SNES_SELECT ? 1 : 0, EV_KEY);
}
