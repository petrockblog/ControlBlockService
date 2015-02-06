installservice:
	apt-get install -y python-smbus i2c-tools libi2c-dev
	if [ -f /etc/modprobe.d/raspi-blacklist.conf ]; then sed -i -e "s|^blacklist i2c-bcm2708|#blacklist i2c-bcm2708|g" /etc/modprobe.d/raspi-blacklist.conf; fi
	./insertLine.sh

	install -m 0755 controlblockservice /etc/init.d
	update-rc.d controlblockservice defaults
	/etc/init.d/controlblockservice start

uninstallservice:
	/etc/init.d/controlblockservice stop
	update-rc.d controlblockservice remove
	-rm /etc/init.d/controlblockservice
