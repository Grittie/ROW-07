#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <time.h>
#include <stdio.h>


#define SRF02_I2C_ADDRESS 0x70

int main() {
    while (true) 
    {
        int fd = wiringPiI2CSetup(SRF02_I2C_ADDRESS);

        if (fd == -1) {
            perror("Unable to open I2C device");
            return 1;
        }

        // Send a command to start a distance measurement
        wiringPiI2CWriteReg8(fd, 0x00, 0x51);

        // Wait for the measurement to complete (about 70ms for SRF02)
        delay(200);
        //delayMicroseconds(70);

        // Read the distance in centimeters
        int distance = wiringPiI2CReadReg16(fd, 0x02);
         
        printf("Distance: %d mm\n", distance/2);
    }
    return 0;
}
