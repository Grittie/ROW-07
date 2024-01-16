#include "waterpump/waterpump.h"
#include "cupDispenser/cupDispenser.h"
#include "servo/servo.h"
#include "wheelEncoder/wheels.h"
#include "mqtt/sub.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <future>
#include <csignal>

#define DISPENSER_PIN 25
#define DISPENSER_TIME 100
#define WATERPUMP_PIN 24
#define EXTRUSION_TIME 5000

using namespace std;

Sub sub;
Wheels wheels;
Waterpump waterpump;
CupDispenser cupDispenser;

bool exitXCase = false;  // Flag to indicate whether to exit 'x' case

void signalHandler(int signum) {
    cout << "Ending program\n";
    wheels.stop();
    exit(signum);
}

void *Listener(void *threadid) {
    cout << "mqtt\n";
    sub.main();
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, signalHandler);

    pthread_t listenerThread;
    pthread_create(&listenerThread, nullptr, Listener, nullptr);

    while (true) {
        char message = sub.return_message();
        switch (message) {
            case 'f':
                wheels.forward();
                break;
            case 'b':
                wheels.backward();
                break;
            case 'l':
                wheels.left();
                break;
            case 'r':
                wheels.right();
                break;
            case 's':
                wheels.stop();
                exitXCase = false;  // Reset the flag when entering 's' case
                break;
            case 'x':
                wheels.stop();
                exitXCase = false;  // Reset the flag before entering 'x' case
                sleep(1);
                printf("TESTING...");

                // Dispense cup
                cupDispenser.dispense(DISPENSER_PIN, DISPENSER_TIME);
                sleep(1);

                // Check cup holder button status
                waterpump.extrude(WATERPUMP_PIN, EXTRUSION_TIME);
                sleep(1);

                // Set the flag to exit 'x' case
                exitXCase = true;
                break;
            default:
                wheels.stop();
                break;
        }

        if (exitXCase) {
            // Exit 'x' case and go to 's' case
            wheels.stop();
            sleep(1);
            printf("Exiting 'x' case and going to 's' case\n");
            // Additional actions or code to handle the transition
            exitXCase = false;  // Reset the flag after handling the transition
        }
    }

    wheels.stop();
    pthread_exit(NULL);
}
