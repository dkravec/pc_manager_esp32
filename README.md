# PC Manager ESP32
Created by Daniel Kravec on May 30, 2024

## Description
This is for the ESP32 microcontroller. There will be a windows counterpart later which this program will interchange data with. 


## Features
This will let you change audio settings on a PC via the ESP32, and possibly via web interface (with another web server, or the ESP32's built in one).

- Potentiometers
- Buttons
- Screens



## Potentiometers
The potentiometers will be used to change the volume of the different apps on the PC.
- Limited to 1-100%, in steps of 10 (or however defined)
- Reads previous value, then value previous to that, decides if it should change the volume or not. 
 - due to potential jitter

Example: 
- going from 50% to 60%: changes
- going from 50% to 55%: doesn't change
- going from 50% to 40%: changes
- going back to 50% from 40% (and 50% before): doesn't change
