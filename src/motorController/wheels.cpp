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
#define LOW_BIT 0x00
#define FORWARD 1
#define BACKWARD 2
#define MAX_SPEED 1023

bool functionCalled = false;

const int fd = wiringPiI2CSetup(WHEEL_ADDRESS);

//wheel encoder array: amount of bits, high bit right, low bit right, direction right, hight bit left, low bit left, direction left

void Wheels::forward() {
    uint8_t Forward[7] = {7,2,0xA5,1,2,0xA5,1};
    write(fd,&Forward[0],7);
}

void Wheels::backward() {
    uint8_t backward[7] = {7,2,0xA5,2,2,0xA5,2};        
    write(fd,&backward[0],7);
}

void Wheels::left() {
    uint8_t left[7] = {7,2,0xA5,1,2,0xA5,2};         
    write(fd,&left[0],7);
}

void Wheels::right() {
    uint8_t right[7] = {7,2,0xA5,2,2,0xA5,1};        
    write(fd,&right[0],7);
}

void Wheels::stop() {
    uint8_t stop[7] = {0x07,0xff,0x00,0x00,0xff,0x00,0x00};
    write(fd,&stop,7);
}


// void Wheels::forward(double x, double y) {
//     if (functionCalled == false) {
//         double inputR = y;
//         double inputL = y;
//         int R = inputR * MAX_SPEED;
//         int L = inputL * MAX_SPEED;
//         uint8_t Forward[7] = {7,(uint8_t)R,(uint8_t)R,FORWARD,(uint8_t)L,(uint8_t)L,FORWARD};
//         write(fd,&Forward[0],7);
//         functionCalled = true;
//     } else {
        
//     }

// }

// void Wheels::forwardLeft(double x, double y) {
//     double inputR = y;
//     double inputL = 1 + x;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t forwardLeft[7] = {7,(uint8_t)R,LOW_BIT,FORWARD,(uint8_t)L,LOW_BIT,FORWARD};
//     write(fd,&forwardLeft[0],7);
// }

// void Wheels::forwardRight(double x, double y) {
//     double inputR = 1 - x;
//     double inputL = y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t forwardRight[7] = {7,(uint8_t)R,LOW_BIT,FORWARD,(uint8_t)L,LOW_BIT,FORWARD};
//     write(fd,&forwardRight[0],7);
// }

// void Wheels::left(double x, double y) {
//     double inputR = -x;
//     double inputL = -x;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t left[7] = {7,(uint8_t)R,LOW_BIT,FORWARD,(uint8_t)L,LOW_BIT,BACKWARD};         
//     write(fd,&left[0],7);
// }

// void Wheels::leftUp(double x, double y) {
//     double inputR = -x;
//     double inputL = y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t leftUp[7] = {7,(uint8_t)R,LOW_BIT,FORWARD,(uint8_t)L,LOW_BIT,FORWARD};         
//     write(fd,&leftUp[0],7);
// }

// void Wheels::leftDown(double x, double y) {
//     double inputR = -x;
//     double inputL = -y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t leftDown[7] = {7,(uint8_t)R,LOW_BIT,BACKWARD,(uint8_t)L,LOW_BIT,BACKWARD};         
//     write(fd,&leftDown[0],7);
// }

// void Wheels::right(double x, double y) {
//     double inputR = x;
//     double inputL = x;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t right[7] = {7,(uint8_t)R,LOW_BIT,BACKWARD,(uint8_t)L,LOW_BIT,FORWARD};        
//     write(fd,&right[0],7);
// }

// void Wheels::rightUp(double x, double y) {
//     double inputR = 1 - x;
//     double inputL = 1 - y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t rightUp[7] = {7,(uint8_t)R,LOW_BIT,FORWARD,(uint8_t)L,LOW_BIT,FORWARD};        
//     write(fd,&rightUp[0],7);
// }

// void Wheels::rightDown(double x, double y) {
//     double inputR = -y;
//     double inputL = x;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t rightDown[7] = {7,(uint8_t)R,LOW_BIT,BACKWARD,(uint8_t)L,LOW_BIT,BACKWARD};        
//     write(fd,&rightDown[0],7);
// }

// void Wheels::backward(double x, double y) {
//     double inputR = -y;
//     double inputL = -y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t backward[7] = {7,(uint8_t)R,(uint8_t)R,BACKWARD,(uint8_t)L,(uint8_t)L,BACKWARD};        
//     write(fd,&backward[0],7);
// }

// void Wheels::backwardLeft(double x, double y) {
//     double inputR = -y;
//     double inputL = 1 + x;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t backwardLeft[7] = {7,(uint8_t)R,LOW_BIT,BACKWARD,(uint8_t)L,LOW_BIT,BACKWARD};        
//     write(fd,&backwardLeft[0],7);
// }

// void Wheels::backwardRight(double x, double y) {
//     double inputR = 1 - x;
//     double inputL = -y;
//     int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     uint8_t backwardRight[7] = {7,(uint8_t)R,LOW_BIT,BACKWARD,(uint8_t)L,LOW_BIT,BACKWARD};        
//     write(fd,&backwardRight[0],7);
// }

// void Wheels::stop() {
//     uint8_t stop[7] = {7,0x00,0x00,0x00,0x00,0x00,0x00};
//     write(fd,&stop[0],7);     
// }

// void Wheels::diagRight(double x, double y) {
//     double inputR = 5;
//     double inputL = x;
//     // int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     // R = R / 4;
//     uint8_t diagRight[7] = {7,(uint8_t)inputR,(uint8_t)inputR,FORWARD,(uint8_t)L,(uint8_t)L,FORWARD};        
//     write(fd,&diagRight[0],7);
// }

// void Wheels::diagLeft(double x, double y) {
//     double inputR = -x;
//     double inputL = 5;
//     int R = inputR * MAX_SPEED;
//     // int L = inputL * MAX_SPEED;
//     // L = L / 4;
//     uint8_t diagLeft[7] = {7,(uint8_t)R,(uint8_t)R,FORWARD,(uint8_t)inputL,(uint8_t)inputL,FORWARD};        
//     write(fd,&diagLeft[0],7);
// }

// void Wheels::diagRightBack(double x, double y) {
//     double inputR = 5;
//     double inputL = x;
//     // int R = inputR * MAX_SPEED;
//     int L = inputL * MAX_SPEED;
//     // R = R / 4;
//     uint8_t diagRightBack[7] = {7,(uint8_t)inputR,(uint8_t)inputR,BACKWARD,(uint8_t)L,(uint8_t)L,BACKWARD};        
//     write(fd,&diagRightBack[0],7);
// }

// void Wheels::diagLeftBack(double x, double y) {
//     double inputR = -x;
//     double inputL = 5;
//     int R = inputR * MAX_SPEED;
//     // int L = inputL * MAX_SPEED;
//     // L = L / 4;
//     uint8_t diagLeftBack[7] = {7,(uint8_t)R,(uint8_t)R,BACKWARD,(uint8_t)inputL,(uint8_t)inputL,BACKWARD};        
//     write(fd,&diagLeftBack[0],7);
// }