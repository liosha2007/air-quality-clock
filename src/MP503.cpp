//
// Created by liosha on 05.01.2022.
//

#include "MP503.h"

MP503::MP503(uint8_t pinA, uint8_t pinB) {
    _pinA = pinA;
    _pinB = pinB;
}

void MP503::initialize() const {
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
    delay(5);
}

uint8_t MP503::readPollution() const {
    int valA = digitalRead(_pinA);
    int valB = digitalRead(_pinB);

    if (valA == 0 && valB == 0) {
        return CLEAN_AIR;
    } else if (valA == 0 && valB == 1) {
        return SLIGHT_POLLUTION_AIR;
    } else if (valA == 1 && valB == 0) {
        return MIDDLE_POLLUTION_AIR;
    } else if (valA == 1 && valB == 1) {
        return HEAVY_POLLUTION_AIR;
    } else {
        return ERROR;
    }
}