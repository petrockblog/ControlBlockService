/*  MCP23017PI library for Raspberry PI converted from Arduino library
    Copyright (C) 2009 David Pye    <davidmpye@gmail.com> (Original Arduino
   Library)
    Copyright (C) 2012 Kasper Skårhøj <kasperskaarhoj@gmail.com> (Original
   Arduino Library)
    Copyright (C) 2013 Isaias Lourenco <isaias.lourenco@swp.pt> (PI conversion)
    Copyright (C) 2014 Florian Müller <contact@petrockblock.com>
    Version 0.1
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mcp23017pi.h"

#include "bcm2835.h"
#include <iostream>
#include <stdio.h>

MCP23017PI::MCP23017PI(uint8_t i2cAddress)
    : _i2cAddress((MCP23017PI_I2C_BASE_ADDRESS >> 1) | (i2cAddress & 0x07)),
      _GPIOA(0), _GPIOB(0), _IODIRA(0), _IODIRB(0), _GPPUA(0), _GPPUB(0) {}

bool MCP23017PI::isBCM2835Initialized = false;

void MCP23017PI::begin() {
    if (!isBCM2835Initialized) {
        if (!bcm2835_init()) {
            printf("Error initializing GPIO.");
            throw 1;
        }
        bcm2835_i2c_setClockDivider(BCM2835_I2C_CLOCK_DIVIDER_626);
        isBCM2835Initialized = true;
    }

    writeRegister(MCP23017PI_IOCON, IOCON_INIT);
}

void MCP23017PI::setPinMode(uint8_t pin, Direction_e dir) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 16) {
        if (pin < 8) {
            reg = MCP23017PI_IODIRA;
            data = &_IODIRA;
        } else {
            reg = MCP23017PI_IODIRB;
            pin &= 0x07;
            data = &_IODIRB;
        }

        if (DIR_INPUT == dir) {
            *data |= (1 << pin);
        } else {
            *data &= (~(1 << pin));
        }
        writeRegister(reg, *data);
    }
}

void MCP23017PI::setPullupMode(uint8_t pin, Pullup_e mode) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 16) {
        if (pin < 8) {
            reg = MCP23017PI_GPPUA;
            data = &_GPPUA;
        } else {
            reg = MCP23017PI_GPPUB;
            pin &= 0x07;
            data = &_GPPUB;
        }

        if (PULLUP_ENABLED == mode) {
            *data |= (1 << pin);
        } else {
            *data &= (~(1 << pin));
        }
        writeRegister(reg, *data);
    }
}

MCP23017PI::Level_e MCP23017PI::digitalRead(uint8_t pin) {
    if (pin < 8) {
        _GPIOA = readRegister(MCP23017PI_GPIOA);
        if (_GPIOA & (1 << pin)) {
            return LEVEL_HIGH;
        } else {
            return LEVEL_LOW;
        }
    } else if (pin < 16) {
        _GPIOB = readRegister(MCP23017PI_GPIOB);
        pin &= 0x07;
        if (_GPIOB & (1 << pin)) {
            return LEVEL_HIGH;
        } else {
            return LEVEL_LOW;
        }
    } else {
        std::cout << "Error while MCP23017PI::digitalRead call. pin="
                  << static_cast<int>(pin) << std::endl;
        throw 11;
    }
}

void MCP23017PI::digitalWrite(uint8_t pin, Level_e level) {
    uint8_t reg;
    uint8_t *data;

    if (pin < 16) {
        if (pin < 8) {
            reg = MCP23017PI_GPIOA;
            data = &_GPIOA;
        } else {
            reg = MCP23017PI_GPIOB;
            pin &= 0x07;
            data = &_GPIOB;
        }

        if (LEVEL_HIGH == level) {
            *data |= 1 << pin;
        } else {
            *data &= ~(1 << pin);
        }
        writeRegister(reg, *data);
    }
}

void MCP23017PI::writeGPIO(uint16_t data) {
    writeRegisterWord(MCP23017PI_GPIOA, data);
}

uint16_t MCP23017PI::readGPIO() { return readRegisterWord(MCP23017PI_GPIOA); }

/*
 * private
 */
void MCP23017PI::writeRegister(uint8_t regAddress, uint8_t data) {
    char buffer[] = {regAddress, data};

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(_i2cAddress);
    uint8_t returnValue = bcm2835_i2c_write(buffer, 2);
    if (returnValue != 0) {
        std::cout << "Something went wrong during writing. regAddress: "
                  << std::hex << static_cast<int>(regAddress)
                  << ", data: " << static_cast<int>(data) << std::endl;
    }
    bcm2835_i2c_end();
}

void MCP23017PI::writeRegisterWord(const uint8_t &regAddress, uint16_t &data) {
    char buffer[] = {regAddress, (uint8_t)data, (uint8_t)(data >> 8)};

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(_i2cAddress);
    uint8_t returnValue = bcm2835_i2c_write(buffer, 3);
    if (returnValue != 0) {
        std::cout << "Something went wrong during writing. regAddress: "
                  << std::hex << static_cast<int>(regAddress)
                  << ", data: " << static_cast<int>(data) << std::endl;
    }
    bcm2835_i2c_end();
}

uint8_t MCP23017PI::readRegister(uint8_t regAddress) {
    char buffer;

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(_i2cAddress);
    uint8_t returnValue =
        bcm2835_i2c_read_register_rs((char *)&regAddress, &buffer, 1);
    if (returnValue != 0) {
        std::cout << "Something went wrong during writing. regAddress: "
                  << std::hex << static_cast<int>(regAddress) << std::endl;
    }
    bcm2835_i2c_end();

    return buffer;
}

uint16_t MCP23017PI::readRegisterWord(uint8_t regAddress) {
    char buffer[2];

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(_i2cAddress);
    uint8_t returnValue =
        bcm2835_i2c_read_register_rs((char *)&regAddress, buffer, 2);
    if (returnValue != 0) {
        std::cout << "Something went wrong during writing. regAddress: "
                  << std::hex << static_cast<int>(regAddress) << std::endl;
    }
    bcm2835_i2c_end();

    return (uint16_t)(((uint16_t)(buffer[1]) << 8) | (uint16_t)buffer[0]);
}

void MCP23017PI::end() { bcm2835_i2c_end(); }
