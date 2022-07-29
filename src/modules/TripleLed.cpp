//
// Created by liosha on 04.01.2022.
//

#include "modules/TripleLed.h"

TripleLed::TripleLed() : _redPin(0), _greenPin(0), _bluePin(0) {
    _ledEnabled = false;
}

void TripleLed::initialize(uint8_t red, uint8_t green, uint8_t blue) {
    _redPin = red;
    _greenPin = green;
    _bluePin = blue;

    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);

    analogWrite(_redPin, 0);
    analogWrite(_greenPin, 0);
    analogWrite(_bluePin, 0);
}

void TripleLed::toggle() {
    if (_ledEnabled) {
        _ledEnabled = false;
        analogWrite(_redPin, 0);
        analogWrite(_greenPin, 0);
        analogWrite(_bluePin, 0);
//        Serial.println("TripleLed was disabled");
    } else {
        _ledEnabled = true;
//        Serial.println("TripleLed was enabled");
    }
}

void TripleLed::update(uint8_t redPart, uint8_t greenPart, uint8_t bluePart) const {
    if (_ledEnabled == false) {
        return;
    }
    analogWrite(_redPin, redPart);
    analogWrite(_greenPin, greenPart);
    analogWrite(_bluePin, bluePart);
}

void TripleLed::allOff() const {
    analogWrite(_redPin, 0);
    analogWrite(_greenPin, 0);
    analogWrite(_bluePin, 0);
}

void TripleLed::redOn() const {
    analogWrite(_redPin, 255);
}

void TripleLed::redOff() const {
    analogWrite(_redPin, 0);
}

void TripleLed::greenOn() const {
    analogWrite(_greenPin, 255);
}

void TripleLed::greenOff() const {
    analogWrite(_greenPin, 0);
}

void TripleLed::blueOn() const {
    analogWrite(_bluePin, 255);
}

void TripleLed::blueOff() const {
    analogWrite(_bluePin, 0);
}
