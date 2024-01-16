#include "cupDispenser.h"
#include <wiringPi.h>
#include <stdio.h>

bool piSetup2 = false;

void CupDispenser::dispense(int dispenserPin, int time) {
    if (piSetup2 == false) {
        wiringPiSetup();
        piSetup2 = true;
        // std::cerr << "WiringPi initialization failed. Exiting program." << std::endl;
        // return 1;
    }
    printStart();
    digitalWrite(dispenserPin, HIGH);
    delay(time);
    digitalWrite(dispenserPin, LOW);
    delay(time);
    printEnd();
}

void CupDispenser::printStart() {
    printf("DISPENSING CUP...\n");
}

void CupDispenser::printEnd() {
    printf("DISPENSING DONE!\n");
}
