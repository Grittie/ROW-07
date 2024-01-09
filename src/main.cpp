#include "waterpump/waterpump.h"
#include "servo/servo.h"
#include "motorController/wheels.h"
#include "mqtt/sub.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <future>
#include <csignal>

// #define servoPin 8
#define waterpumpPin 15

using namespace std;

Sub sub;
Wheels wheels;

void signalHandler(int signum) {

    cout << "Ending program\n";
    wheels.stop();
    exit(signum);
}

void* Listener(void* threadid) {

    cout << "mqtt\n";
    sub.main();

    pthread_exit(NULL);
}


int main() {

    signal(SIGINT, signalHandler);
    // Waterpump waterpump;
    // int waterpumpPin = 15; // Set the value you want to pass for the pin
    // int extrusionTime = 3000; // Set the value you want to pass for the extrusion time
    // waterpump.extrude(waterpumpPin, extrusionTime); // Pass the pinNumber and extrusionTime as an argument
    // // int servoPin = 8;
    // Waterpump waterpump;
    // Servo frontServo;

    pthread_t listenerThread;

    pthread_create(&listenerThread, nullptr, Listener, nullptr);

    // x/y range: -1 - 1

    // wheels.stop();

    // double x = 0;
    // double y = 0;

    while (true) { 
        char message = sub.return_message();
        switch (message)
        {
            case 'f':
            {
                wheels.forward();
                break;
            }
            case 'b':
            {
                wheels.backward();
                break;
            }
            case 'l':
            {
                wheels.left();
                break;
            }
            case 'r':
            {
                wheels.right();
                break;
            }
            case 's':
            {
                wheels.stop();
                break;
            }
            default:
            {
                wheels.stop();
                break;
            }
        }
    }

    pthread_exit(NULL);

}

    //     if(x == 0 && y == 0) {
    //         wheels.stop();
    //     }else if(y >= -0.2 && y <= 0.2 && x < 0) {
    //         cout << "Left\n";
    //         wheels.left(x, y);
    //     }else if(y >= -0.2 && y <= 0.2 && x > 0) {
    //         cout << "Right\n";
    //         wheels.right(x, y);
    //     }else if(y > 0.2) {
    //         if (x >= -0.2 && x <= 0.2) {
    //             cout << "forward\n";
    //             wheels.forward(x, y);
    //         }else if (x <= -0.1 && x >= -0.5) {
    //             cout << "Slight left\n";
    //             wheels.forwardLeft(x, y);
    //         }else if (x <= -0.6 && x >= -1.0) {
    //             cout << "left, slightly forward\n";
    //             wheels.leftUp(x, y);
    //         }else if (x >= 0.1 && x <= 0.5) {
    //             cout << "Slight right\n";
    //             wheels.forwardRight(x, y);
    //         }else if (x >= 0.6 && x <= 1.0) {
    //             cout << "right, slightly forward\n";
    //                 wheels.rightUp(x, y);
    //         }
    //     }else if(y < -0.2) {
    //         if (x >= -0.2 && x <= 0.2) {
    //             cout << "backward";
    //             wheels.backward(x, y);
    //         }else if (x <= -0.1 && x >= -0.5) {
    //             cout << "Slight backLeft\n";
    //             wheels.backwardLeft(x, y);
    //         }else if (x <= -0.6 && x >= -1.0) {
    //             cout << "left, slightly down\n";
    //             wheels.leftDown(x, y);
    //         }else if (x >= 0.1 && x <= 0.5) {
    //             cout << "Slight backRight\n";
    //             wheels.backwardRight(x, y);
    //         }else if (x >= 0.6 && x <= 1.0) {
    //             cout << "right, slightly down\n";
    //             wheels.rightDown(x, y);
    //         }
    //     }else {
    //         cout << "no valid input\n";
    //         wheels.stop();
    //     }
    // }