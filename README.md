ControlBlockService
===================

This is the driver for the petrockblock.com ControlBlock, which is an extension board for the Raspberry Pi (TM). The driver itself is denoted as _controlblock_ in the following. The driver provides a service for interacting with the power button signals as well as for mapping attached game controllers to corresponding game pad devices on the Raspberry Pi.

## Downloading

If you would like to download the latest version of _controlblock_ from [its Github repository](https://github.com/petrockblog/ControlBlockService), you can use this command:
```bash
git clone https://github.com/petrockblog/ControlBlockService.git
```

## Building and Installation

To build _controlblock_ follow these commands:
```bash
cd ControlBlockService
make
```

If everything went fine you can install with the command
```bash
sudo make install
```

## Installation as Service

You can install _controlblock_ as daemon with this command:
```bash
sudo make installservice
```

## Uninstalling the service and/or the binary

You can uninstall the daemon with this command:
```bash
sudo make uninstallservice
```

You can uninstall the binary with this command:
```bash
sudo make uninstall
```

<br><br>
__Have fun!__

-Florian [petrockblock.com](http://blog.petrockblock.com)