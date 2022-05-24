//
// Created by liosha on 05.01.2022.
//

#include "MP503.h"

MP503::MP503(uint8_t pinA, uint8_t pinB) {
    _pinA = pinA;
    _pinB = pinB;
    _pollution = 0;
}

bool MP503::initialize() const {
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
    delay(5);
    return true;
}

uint8_t MP503::readPollution(uint32_t currentMillis) {
    if (currentMillis % UPDATE_MP503 || _pollution == 0 /* Initial load */) {
        int valA = digitalRead(_pinA);
        int valB = digitalRead(_pinB);

        if (valA == 0 && valB == 0) {
            _pollution = CLEAN_AIR;
        } else if (valA == 0 && valB == 1) {
            _pollution = SLIGHT_POLLUTION_AIR;
        } else if (valA == 1 && valB == 0) {
            _pollution = MIDDLE_POLLUTION_AIR;
        } else if (valA == 1 && valB == 1) {
            _pollution = HEAVY_POLLUTION_AIR;
        } else {
            _pollution = ERROR;
        }

        Serial.print("New pollution value (1-4) = ");
        Serial.println(_pollution);
    }
    return _pollution;
}