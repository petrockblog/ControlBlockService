#include "I2C8bit.h"

#include <iostream>

using namespace std;
/*****************************************************************
 * This is the default constructor for the class. It assigns
 * all private variables to default values and calls the openI2C()
 * function to open the default I2C device "/dev/i2c-0".
 *****************************************************************/
I2C8Bit::I2C8Bit(void)
{
	this->i2cFileName = "/dev/i2c-0";
	this->deviceAddress= 0;
	this->i2cDescriptor = -1;
//        cout << " Opening I2C Device" << endl;
	this->openI2C();

}

/*******************************************************************
 * This is the overloaded constructor. It allows the programmer to
 * specify a custom I2C device & device address
 * The device descriptor is determined by the openI2C() private member
 * function call.
 * *****************************************************************/

I2C8Bit::I2C8Bit(unsigned char dev_addr, std::string i2c_file_name)
{
	this->i2cFileName = i2c_file_name;
	this->deviceAddress = dev_addr;
	this->i2cDescriptor = -1;
	//      cout << " Opening I2C Device" << endl;
	this->openI2C();
}
/**********************************************************************
 * This is the class destructor it simply closes the open I2C device
 * by calling the closeI2C() which in turn calls the close() system call
 * *********************************************************************/

I2C8Bit::~I2C8Bit(void)
{
	//    cout << " Closing I2C Device" << endl;
	this->closeI2C();
}

/**********************************************************************
 * This function opens the I2C device by simply calling the open system
 * call on the I2C device specified in the i2cFileName string. The I2C
 * device is opened for writing and reading. The i2cDescriptor private
 * variable is set by the return value of the open() system call.
 * This variable will be used to reference the opened I2C device by the
 * ioctl() & close() system calls.
 * ********************************************************************/

int I2C8Bit::openI2C()
{
	this->i2cDescriptor = open(i2cFileName.c_str(), O_RDWR);
	if(i2cDescriptor < 0) {
		perror("Could not open file (1)");
		exit(1);
	}

	return i2cDescriptor;
}

/*********************************************************************
 * This function closes the I2C device by calling the close() system call
 * on the I2C device decriptor.
 * *******************************************************************/

int I2C8Bit::closeI2C()
{
	int retVal = -1;
	retVal = close(this->i2cDescriptor);
	if(retVal < 0) {
		perror("Could not close file (1)");
		exit(1);
	}
	return retVal;
}
/********************************************************************
 *This function writes a byte of data "data" to a specific register
 *"reg_addr" in the I2C device This involves sending these two bytes
 *in order to the i2C device by means of the ioctl() command. Since
 *both bytes are written (no read/write switch), both pieces
 *of information can be sent in a single message (i2c_msg structure)
 ********************************************************************/
int I2C8Bit::writeReg(unsigned char reg_addr, unsigned char data)
{

	unsigned char buff[2];
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[1];

	buff[0] = reg_addr;
	buff[1] = data;

	messages[0].addr = deviceAddress;
	messages[0].flags = 0;
	messages[0].len = sizeof(buff);
	messages[0].buf = buff;



	packets.msgs = messages;
	packets.nmsgs = 1;

	retVal = ioctl(this->i2cDescriptor, I2C_RDWR, &packets);
	if(retVal < 0)
		perror("Write to I2C Device failed");

	return retVal;
}

/********************************************************************
 *This function reads a byte of data "data" from a specific register
 *"reg_addr" in the I2C device. This involves sending the register
 *byte "reg_Addr" with "write" asserted and then instructing the
 *I2C device to read a byte of data from that address ("read asserted").
 *This necessitates the use of two i2c_msg structs. One for the register
 *address write and another for the read from the I2C device i.e.
 *I2C_M_RD flag is set. The read data is then saved into the reference
 *variable "data".
 ********************************************************************/

int I2C8Bit::readReg(unsigned char reg_addr, unsigned char &data)
{

	unsigned char *inbuff, outbuff;
	int retVal = -1;
	struct i2c_rdwr_ioctl_data packets;
	struct i2c_msg messages[2];

	outbuff = reg_addr;
	messages[0].addr = deviceAddress;
	messages[0].flags= 0;
	messages[0].len = sizeof(outbuff);
	messages[0].buf = &outbuff;


	inbuff = &data;
	messages[1].addr = deviceAddress;
	messages[1].flags = I2C_M_RD;
	messages[1].len = sizeof(*inbuff); // size of value pointed to by inbuff to size of pointer inbuff
	messages[1].buf = inbuff;


	packets.msgs = messages;
	packets.nmsgs = 2;

	retVal = ioctl(this->i2cDescriptor, I2C_RDWR, &packets);
	if(retVal < 0)
		perror("Read from I2C Device failed");

	return retVal;
}
