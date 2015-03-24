#!/bin/bash
echo -e "Making sure that i2c-dev is contained in /etc/modules ..."
if [[ -z $(cat /etc/modules | grep i2c-dev) ]]; then
	sed -i '$a i2c-dev' /etc/modules
fi
echo "options i2c_bcm2708 baudrate=1700000" > /etc/modprobe.d/i2c.conf
modprobe i2c-bcm2708
modprobe i2c_dev

echo -e "Making sure that uinput is contained in /etc/modules ..."
if [[ -z $(cat /etc/modules | grep uinput) ]]; then
	sed -i '$a uinput' /etc/modules
fi
modprobe uinput

echo -e "Making sure that the ARM I2C Interface is enabled via /boot/config.txt ..."
if [[ -z $(cat /boot/config.txt | grep dtparam=i2c_arm=on) ]]; then
    sed -i '$a dtparam=i2c_arm=on' /boot/config.txt
fi

if [[ -z $(cat /boot/config.txt | grep dtparam=i2c_arm_baudrate=1700000) ]]; then
    sed -i '$a dtparam=i2c_arm_baudrate=1700000' /boot/config.txt
fi
