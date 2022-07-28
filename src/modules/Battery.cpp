//
// Created by liosha on 23.05.2022.
//

#include <Arduino.h>
#include "modules/Battery.h"

Battery::Battery() : _pin(0) {
}

void Battery::init(uint8_t pin) {
    _pin = pin;
    pinMode(_pin, INPUT);
}

uint8_t Battery::readLevel(uint8_t min, uint8_t max) const {
    int16_t rawLevel = analogRead(_pin);
    uint8_t level = map(rawLevel, BUTTERY_MIN_RAW, BUTTERY_MAX_RAW, min, max);

    Serial.print("BUTTERY value (0-160) = ");
    Serial.print(level);
    Serial.print(", raw = ");
    Serial.println(rawLevel);
    return level;
}
