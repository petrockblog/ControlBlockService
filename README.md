ControlBlockService
===================

[![Build Status](https://travis-ci.org/petrockblog/ControlBlockService.svg?branch=master)](https://travis-ci.org/petrockblog/ControlBlockService)

This is the driver for the petrockblock.com ControlBlock, which is an extension board for the Raspberry Pi (TM). The driver itself is denoted as _controlblock_ in the following. The driver provides a service for interacting with the power button signals as well as for mapping attached game controllers to corresponding game pad devices on the Raspberry Pi.

**Please note that this is the driver for revision 1.X of the ControlBlock. If you have a revision 2.X board, you need to use the [driver for that revision series](https://github.com/petrockblog/ControlBlockService2).**

## Downloading

If you would like to download the latest version of _controlblock_ from [its Github repository](https://github.com/petrockblog/ControlBlockService), you can use this command:
```bash
git clone https://github.com/petrockblog/ControlBlockService.git
```

## Prerequisites

To be able to successfully build ControlBlockService you need to have certain APT packages installed. You can make sure that you have the latest version of those packages with these commands:

```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y cmake g++-4.8
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
It might be that you need to **restart** your Raspberry afterwards to have all needed services running.

## Uninstalling the service and/or the binary

You can uninstall the daemon with this command:
```bash
sudo make uninstallservice
```

You can uninstall the binary with this command:
```bash
sudo make uninstall
```

## Configuration

The configuration file of _controlblock_ is located at ```/etc/controlblockconfig.cfg```. It uses JSON syntax for setting the the values of its configuration parameters.

The parameters are explained in detail in the following:

 - ```input - gamepadtype```: Can be set to 
     + ```arcade```: Enables two game pads in the system and maps the GPIOs of the ControlBlock to these game pads.<br>
     ![ArcadeMapping](https://github.com/petrockblog/ControlBlockService/raw/master/supplementary/ControlBlockLayoutArcade.png)
     + ```mame```: Enables a virtual keyboard and maps the GPIOs of the ControlBlock to this keyboard with a MAME layout.<br>
     ![ArcadeMapping](https://github.com/petrockblog/ControlBlockService/raw/master/supplementary/ControlBlockLayoutMAME.png)
     + ```snes```: Enables two game pads in the system and maps the attached SNES/NES controllers accordingly.<br>
     ![ArcadeMapping](https://github.com/petrockblog/ControlBlockService/raw/master/supplementary/ControlBlockLayoutSNESNES.png)
 - ```input - singlegamepad```: Can be set to 
     + ```true```: Enables only one gamepad in the system (eg if only Player1 buttons are wired to the controlblock in your setup, this prevents a ghost gamepad from being selected as default player 2 in retroarch)
     + ```false```: Enables the two gamepads (default)
 - ```powerswitch - activated```: Can be set to
     + ```true```: Activates the handling of the power switch signals of the ControlBlock.
     + ```false```: Deactivates the handling of the power switch signals of the ControlBlock.

<br><br>
__Have fun!__

-Florian [petrockblock.com](http://blog.petrockblock.com)
