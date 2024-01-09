#include "waterpump.h"
#include <wiringPi.h>
#include <stdio.h>

void Waterpump::extrude(int in, int time) { // Keep the 'int in' parameter
    wiringPiSetup();
    printStart();
    digitalWrite(in, HIGH);
    delay(time);
    digitalWrite(in, LOW);
    printEnd();
}

void Waterpump::printStart() {
    printf("EXTRUDING...\n");
}

void Waterpump::printEnd() {
    printf("EXTRUDING DONE!\n");
}
