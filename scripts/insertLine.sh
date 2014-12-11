#!/bin/bash
echo -e "Making sure that o2c-dev is contained in /etc/modules ..."
if [[ -z $(cat /etc/modules | grep i2c-dev) ]]; then
	sed -i '$a i2c-dev' /etc/modules
fi
echo "options i2c_bcm2708 baudrate=1700000" > /etc/modprobe.d/i2c.conf
modprobe i2c-bcm2708
modprobe i2c_dev
