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

#ifndef UINPUTCPP_H
#define UINPUTCPP_H

#include <stdint.h>
extern "C" {
#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
}

class UInputcpp {
  public:
    UInputcpp() {}
    ~UInputcpp() {}

    static int32_t getHandle() {
        int32_t handle = open("/dev/uinput", O_WRONLY | O_NDELAY);
        if (handle == 0) {
            printf("Unable to open /dev/uinput\n");
            throw 1;
        }
        return handle;
    }

    static void releaseHandle(int32_t handle) {
        ioctl(handle, UI_DEV_DESTROY);
        close(handle);
    }

    static void setKeyState(int32_t uinp_fd, uint16_t keycode, int16_t keyvalue,
                            uint16_t evtype) {
        struct input_event event;
        gettimeofday(&event.time, NULL);

        event.type = evtype;
        event.code = keycode;
        event.value = keyvalue;

        if (write(uinp_fd, &event, sizeof(event)) < 0) {
            printf("[UInputGamepad] Simulate key error\n");
        }

        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        write(uinp_fd, &event, sizeof(event));
        if (write(uinp_fd, &event, sizeof(event)) < 0) {
            printf("[UInputGamepad] Simulate key error\n");
        }
    }

  private:
};

#endif
