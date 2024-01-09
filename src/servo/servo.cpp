#include <wiringPi.h>
#include "servo.h"
#include <softPwm.h>
#include <iostream>
#include <unistd.h>

void Servo::left(int in) { // Keep the 'int in' parameter
    wiringPiSetup();
    softPwmCreate(in, 0, 200); // Create a software PWM pin
    printLeft();
    softPwmWrite(in, 10); // 10 is the minimum angle (adjust as needed)
    delay(1000); // Wait for 1 second
    printDone();
}

void Servo::right(int in) { // Keep the 'int in' parameter
    wiringPiSetup();
    softPwmCreate(in, 0, 200); // Create a software PWM pin
    printRight();
    softPwmWrite(in, 20); // 20 is the maximum angle (adjust as needed)
    delay(1000); // Wait for 1 second
    printDone();
}

void Servo::printLeft() {
    printf("GOING LEFT...\n");
}

void Servo::printRight() {
    printf("GOING RIGHT....\n");
}

void Servo::printDone() {
    printf("MOVEMENT COMPLETE.\n");
}
