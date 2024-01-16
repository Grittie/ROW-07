#include "waterpump.h"
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

bool piSetup = false;

// void Waterpump::extrude(int in, int time) {
//     wiringPiSetup();

//     // Print values of in and time before extruding
//     printf("Extruding with in=%d and time=%d\n", in, time);

//     printStart();
//     digitalWrite(in, HIGH);
//     delay(time);
//     digitalWrite(in, LOW);
//     printEnd();
// }

void Waterpump::extrude(int in, int time) {
    if (piSetup == false) {
        wiringPiSetup();
        piSetup = true;
        // std::cerr << "WiringPi initialization failed. Exiting program." << std::endl;
        // return 1;
    }
    printStart();
    digitalWrite(in, HIGH);
    delay(time);
    digitalWrite(in, LOW);
    delay(time);
    printEnd();
}

void Waterpump::printStart() {
    printf("EXTRUDING...\n");
}

void Waterpump::printEnd() {
    printf("EXTRUDING DONE!\n");
}
