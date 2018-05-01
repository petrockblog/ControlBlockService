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

#ifndef MCP23017PI_H
#define MCP23017PI_H

#include <stdint.h>

class MCP23017PI {
  public:
    /*
    * NB the i2c address here is the value of the A0, A1, A2 pins ONLY
    * as the class takes care of its internal base address.
    * so i2cAddress should be between 0 and 7
    */
    explicit MCP23017PI(uint8_t i2cAddress);
    void begin();
    void end();

    // These functions provide an 'arduino'-like functionality for accessing
    // pin states/pullups etc.
    typedef enum { DIR_INPUT = 0, DIR_OUTPUT } Direction_e;

    typedef enum { LEVEL_LOW = 0, LEVEL_HIGH } Level_e;

    typedef enum { PULLUP_ENABLED = 0, PULLUP_DISABLED } Pullup_e;

    void setPinMode(uint8_t pin, Direction_e dir);
    void setPullupMode(uint8_t pin, Pullup_e mode);
    void digitalWrite(uint8_t pin, Level_e val);
    Level_e digitalRead(uint8_t pin);

    void writeGPIO(uint16_t data);
    uint16_t readGPIO();

  private:
    const uint8_t MCP23017PI_IODIRA = 0x00;
    const uint8_t MCP23017PI_IODIRB = 0x01;
    const uint8_t MCP23017PI_IPOLA = 0x2;
    const uint8_t MCP23017PI_IPOLB = 0x3;
    const uint8_t MCP23017PI_GPIOA = 0x12;
    const uint8_t MCP23017PI_GPIOB = 0x13;
    const uint8_t MCP23017PI_OLATA = 0x14;
    const uint8_t MCP23017PI_OLATB = 0x15;
    const uint8_t MCP23017PI_IOCON = 0x0A;
    const uint8_t MCP23017PI_GPPUA = 0x0C;
    const uint8_t MCP23017PI_GPPUB = 0x0D;

    // Bits in the IOCON register
    const uint8_t IOCON_UNUSED = 0x01;
    const uint8_t IOCON_INTPOL = 0x02;
    const uint8_t IOCON_ODR = 0x04;
    const uint8_t IOCON_HAEN = 0x08;
    const uint8_t IOCON_DISSLW = 0x10;
    const uint8_t IOCON_SEQOP = 0x20;
    const uint8_t IOCON_MIRROR = 0x40;
    const uint8_t IOCON_BANK_MODE = 0x80;

    // Default initialisation mode
    const uint8_t IOCON_INIT = 0x20;  // IOCON_SEQOP from above

    const uint8_t MCP23017PI_I2C_BASE_ADDRESS = 0x40;

    void writeRegister(uint8_t regaddress, uint8_t val);
    void writeRegisterWord(const uint8_t &regAddress, uint16_t &data);
    uint8_t readRegister(uint8_t regaddress);
    uint16_t readRegisterWord(uint8_t regaddress);

    uint8_t _i2cAddress;
    uint8_t _GPIOA, _GPIOB;
    uint8_t _IODIRA, _IODIRB;
    uint8_t _GPPUA, _GPPUB;

    static bool isBCM2835Initialized;
};
#endif
