#!/bin/bash
echo "***********************************************************************************"
echo "* Test Script to Check for the Correct Functionality of the ControlBlock GPIOs    *"
echo "* www.petrockblock.com                                                            *"
echo "*                                                                                 *"
echo "* Preparation: Remove the ControlBlock and any other hardware connected to the    *"
echo "* GPIO pins. Also stop the ControlBlock service via the command                   *"
echo "*                    sudo service controlblockservice stop                        *"
echo "*                                                                                 *"
echo "* To check for the correct functionality of the pins that the ControlBlock uses   *"
echo "* connect a jumper wire to GND (pin 6) and cautiously connect it with these pins: *"
echo "* 11, 12, 19, 21, 23, 24. For every of these pins a message of the form           *" 
echo "* \"Found GPIO x\" must be printed to the output.                                 *"
echo "* Do not get confused with the printed GPIO numbers. That are the original BCM    *"
echo "* pin numbers.                                                                    *"
echo "*                                                                                 *"
echo "* You can exit this bash script by pressing Ctrl-C.                               *"
echo "***********************************************************************************"
echo ""

pinNumbers=(8 9 10 11 17 18) 

# trap ctrl-c and call ctrl_c()
trap ctrl_c INT
function ctrl_c() {
    echo "** Trapped CTRL-C"

    # Clean up
    for index in pinNumbers; do
        echo "${index}" > /sys/class/gpio/unexport
    done
    exit 130
}

# Note that the GPIO numbers that you program here refer to the pins
# of the BCM2835 and *not* the numbers on the pin header. 
# So, if you want to activate GPIO7 on the header you should be 
# using GPIO4 in this script. Likewise if you want to activate GPIO0
# on the header you should be using GPIO17 here.
function setPinAsInput() {
    local pin=$1
    # Set up GPIO 4 and set to output
    echo "${pin}" > /sys/class/gpio/export
    sleep 0.25
    echo "in" > /sys/class/gpio/gpio${pin}/direction
    sleep 0.25
    echo "high" > /sys/class/gpio/gpio${pin}/direction
    sleep 0.25
} 
 
# Set up GPIO 7 and set to input
for index in ${pinNumbers[@]}; do
    setPinAsInput ${index}
done
 
while true; do
    for index in ${pinNumbers[@]}; do
        pinValue="/sys/class/gpio/gpio${index}/value"
        value=`cat ${pinValue}`
        if [[ "${value}" == "0" ]]; then
            echo "Found GPIO ${index}"
            sleep 0.25
        fi
    done
done
