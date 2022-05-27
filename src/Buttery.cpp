//
// Created by liosha on 23.05.2022.
//

#include <Arduino.h>
#include "Buttery.h"

Buttery::Buttery(uint8_t pin) {
    _pin = pin;
    _level = 0;
}

void Buttery::initialize() const {
    pinMode(_pin, INPUT);
}

uint8_t Buttery::readLevel(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_BUTTERY) == 0 || _level == 0 /* Initial load */) {
        _level = analogRead(_pin);

        Serial.print("BUTTERY value (0-160) = ");
        Serial.print(displayableLevel(_level));
        Serial.print(", raw = ");
        Serial.println(_level);
    }
    return displayableLevel(_level);
}

uint8_t Buttery::displayableLevel(int16_t level) {
    return map(level, BUTTERY_MIN_RAW, BUTTERY_MAX_RAW, BUTTERY_MIN, BUTTERY_MAX);;
}
