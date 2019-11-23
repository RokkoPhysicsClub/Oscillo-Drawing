#include "oscillofunction.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

int main(void) {
    // setup
    if(wiringPiSetup() == -1) {
        return 1;
    } else {
        // X Axis
        pinMode(0, OUTPUT); // pin17
        pinMode(1, OUTPUT); // pin18
        pinMode(2, OUTPUT); // pin27
        pinMode(3, OUTPUT); // pin22
        pinMode(4, OUTPUT); // pin23
        pinMode(5, OUTPUT); // pin24
        pinMode(6, OUTPUT); // pin25
        pinMode(7, OUTPUT); // pin4

        // Y Axis
        pinMode(8, OUTPUT);  // pin2
        pinMode(9, OUTPUT);  // pin3
        pinMode(10, OUTPUT); // pin8
        pinMode(11, OUTPUT); // pin7
        pinMode(12, OUTPUT); // pin10
        pinMode(13, OUTPUT); // pin9
        pinMode(14, OUTPUT); // pin11
        pinMode(15, OUTPUT); // pin14
    }

    // Edit here.

    return 0;
}