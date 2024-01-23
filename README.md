# Row 07

This is the git repository for the Robot on Wheels project for group 07.


## Project idea

Beverage bot is a drink dispensing and cup disposal robot. The beverage bot can be used to supply users of drinks and can dispose of the cups thrown on the ground after consumption.


## Authors

- [Lars Grit](https://gitlab.fdmci.hva.nl/gritla)
- [Ayham Nahar](https://gitlab.fdmci.hva.nl/nahara)
- [Luc Enderman](https://gitlab.fdmci.hva.nl/enderml)
- [Silvester Rademaker](https://gitlab.fdmci.hva.nl/rademas1)


## Demo

![Animated GIF](docs/img/extrude.gif)



## Documentation

### Pi Configuration

**Operating System (OS) Version:**
- Raspberry Pi OS Lite 32-bit (Debian Bookworm)

**System Information:**
- Raspberry Pi 4 Model

**Network Configuration:**
   - Connected to a hotspot; the app requiring communication should be on the same network.

**Peripheral Devices:**
   - Raspberry Pi Camera Module connected.

**Filesystem and Storage:**
   - 32GB SD card.
   - Filesystem: ext4

**User Accounts:**
   - Default User: pi
   - Additional Users: raspberry

**SSH Configuration:**
   - Default SSH port: 22 (or specify if you've changed it)

**Additional Notes:**
    - It is recommended to set up a static IP address for the Raspberry Pi for consistent network communication. Instructions for setting up a static IP can be found [here](https://www.tomshardware.com/how-to/static-ip-raspberry-pi).


## Additional software documentation
Further documentation can be found below in the documentation index: [Documentation](/docs/index.md)


## Features

- Beverage dispensing
- Cup dispensing
- App remote control
- Video feed 
- Computer vision cup detection


## Installation

For pi:
```bash
cd pi
mkdir build
cd build
cmake ..
cmake --build .
./main
```
## Tech Stack
- Python
    - OpenCV
    - Flask
- C++
- Java (for app)
