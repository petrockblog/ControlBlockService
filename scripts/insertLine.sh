#!/bin/bash
echo -e "Making sure that o2c-dev is contained in /etc/modules ..."
if [[ -z $(cat /etc/modules | grep i2c-dev) ]]; then
	sed -i '$a i2c-dev' /etc/modules
fi
modprobe i2c-bcm2708
modprobe i2c_dev
