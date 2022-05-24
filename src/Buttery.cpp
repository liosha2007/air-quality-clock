//
// Created by liosha on 23.05.2022.
//

#include <Arduino.h>
#include "Buttery.h"

Buttery::Buttery(uint8_t pin) {
    _pin = pin;
    _level = 0;
}

uint8_t Buttery::readLevel(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_BUTTERY) == 0 || _level == 0 /* Initial load */) {
        long value = analogRead(_pin);
        _level = map(value, BUTTERY_MIN_RAW, BUTTERY_MAX_RAW, BUTTERY_MIN, BUTTERY_MAX);

        Serial.print("New buttery value (0-5) = ");
        Serial.println(_level);
    }
    return _level;
}