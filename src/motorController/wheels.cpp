#include "wheels.h"
#include <wiringPiI2C.h> // je kan ook pigpio gebruiken
#include <wiringPi.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define WHEEL_ADDRESS 0x32
#define FORWARD 1
#define BACKWARD 2

const int fd = wiringPiI2CSetup(WHEEL_ADDRESS);

//wheel encoder array: amount of bits, high bit right, low bit right, direction right, hight bit left, low bit left, direction left

void Wheels::forward() {
    uint8_t Forward[7] = {7,0xA,0xFF,FORWARD,0xA,0xFF,FORWARD};
    write(fd,&Forward,7);
}

void Wheels::backward() {
    uint8_t backward[7] = {7,0xA,0xFF,BACKWARD,0xA,0xFF,BACKWARD};        
    write(fd,&backward,7);
}

void Wheels::left() {
    uint8_t left[7] = {7,0xA,0xFF,FORWARD,0xA,0xFF,BACKWARD};         
    write(fd,&left,7);
}

void Wheels::right() {
    uint8_t right[7] = {7,0xA,0xFF,BACKWARD,0xA,0xFF,FORWARD};        
    write(fd,&right,7);
}

void Wheels::stop() {
    uint8_t stop[7] = {0x07,0x00,0x00,0x00,0x00,0x00,0x00};
    write(fd,&stop,7);
}