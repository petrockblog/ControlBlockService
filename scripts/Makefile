installservice:
	install -m 0755 controlblockservice /etc/init.d
	update-rc.d controlblockservice defaults
	/etc/init.d/controlblockservice start

uninstallservice:
	/etc/init.d/controlblockservice stop
	update-rc.d controlblockservice remove
	-rm /etc/init.d/controlblockservice
