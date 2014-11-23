#ifndef I2C8BIT_H
#define I2C8BIT_H

#include <string>
#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

class I2C8Bit
{
public:
	I2C8Bit(void); // default constructor
	I2C8Bit(unsigned char dev_addr, std::string i2cfilename);
	//over loaded constructor
	~I2C8Bit(void); // destructor
	int writeReg(unsigned char reg_addr, unsigned char data);
	// function to write byte data into a register of an I2C device
	int readReg(unsigned char reg_addr, unsigned char &data);
	// function to read byte data from a register of an I2C device

private:
	//private member functions
	int openI2C(); //open an I2C device. Called only in constructors
	int closeI2C(); // close an I2C device. Called only in destructor

	// private member variables
	std::string  i2cFileName; //i2c device name e.g."/dev/i2c-0" or "/dev/i2c-1"
	int i2cDescriptor;  // i2c device descriptor
	unsigned char deviceAddress; // i2c device address
};

#endif // I2C8BIT_H
