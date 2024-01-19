#include "waterpump.h"
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>

bool piSetup = false;

void Waterpump::extrude(int in, int time) {
    if (piSetup == false) {
        wiringPiSetup();
        piSetup = true;
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
