#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include "ultrasound.h"

Ultrasound::Ultrasound() {
    if (wiringPiSetup() == -1) {
        perror("Unable to initialize wiringPi");
        exit(1);
    }
}

void Ultrasound::measureDistance() {
    int fd = wiringPiI2CSetup(SRF02_I2C_ADDRESS);

    if (fd == -1) {
        perror("Unable to open I2C device");
        exit(1);
    }

    // Send a command to start a distance measurement
    wiringPiI2CWriteReg8(fd, 0x00, 0x51);

    // Wait for the measurement to complete (about 70ms for SRF02)
    usleep(200000); // Sleep for 200 milliseconds

    // Read the distance in centimeters
    int distance = wiringPiI2CReadReg16(fd, 0x02);

    std::cout << "Distance: " << distance / 2 << " mm" << std::endl;
}

