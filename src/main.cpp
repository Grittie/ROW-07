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
            case 'p':
            {
                wheels.stop();
                sleep(1);

                break;
            }
            default:
            {
                wheels.stop();
                break;
            }
        }
    }

    wheels.stop();

    pthread_exit(NULL);

}