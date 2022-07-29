//
// Created by liosha on 05.01.2022.
//

#include "modules/MP503.h"

MP503::MP503() : _pinA(0), _pinB(0) {
}

bool MP503::init(uint8_t pinA, uint8_t pinB) {
    _pinA = pinA;
    _pinB = pinB;
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
    return true;
}

uint8_t MP503::readPollution() const {
    int valA = digitalRead(_pinA);
    int valB = digitalRead(_pinB);

    uint8_t pollution = 0;
    if (valA == 0 && valB == 0) {
        pollution = CLEAN_AIR;
    } else if (valA == 0 && valB == 1) {
        pollution = SLIGHT_POLLUTION_AIR;
    } else if (valA == 1 && valB == 0) {
        pollution = MIDDLE_POLLUTION_AIR;
    } else if (valA == 1 && valB == 1) {
        pollution = HEAVY_POLLUTION_AIR;
    } else {
        pollution = ERROR;
    }

//    Serial.print("MP503: pollution (1-4) = ");
//    Serial.println(pollution);
    return pollution;
}