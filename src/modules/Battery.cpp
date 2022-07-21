//
// Created by liosha on 23.05.2022.
//

#include <Arduino.h>
#include "modules/Battery.h"

Battery::Battery() : _pin(0), _level(0) {
}

void Battery::init(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
}

uint8_t Battery::readLevel() {
    if (_level == 0 /* Initial load */) {
        _level = analogRead(_pin);

        Serial.print("BUTTERY value (0-160) = ");
        Serial.print(displayableLevel(_level));
        Serial.print(", raw = ");
        Serial.println(_level);
    }
    return displayableLevel(_level);
}

uint8_t Battery::displayableLevel(int16_t level) {
    return map(level, BUTTERY_MIN_RAW, BUTTERY_MAX_RAW, BUTTERY_MIN, BUTTERY_MAX);
}
