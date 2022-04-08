//
// Created by liosha on 04.01.2022.
//

#include "TripleLed.h"

TripleLed::TripleLed(uint8_t red, uint8_t green, uint8_t blue) {
    redPin = red;
    greenPin = green;
    bluePin = blue;
    ledEnabled = false;
}

void TripleLed::initialize() const {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);

    blinkRed(133);
    delay(50);
    blinkRed(133);
    delay(50);
    blinkRed(133);

    blinkGreen(133);
    delay(50);
    blinkGreen(133);
    delay(50);
    blinkGreen(133);

    blinkBlue(133);
    delay(50);
    blinkBlue(133);
    delay(50);
    blinkBlue(133);
}

void TripleLed::toggle() {
    if (ledEnabled) {
        ledEnabled = false;
        analogWrite(redPin, 0);
        analogWrite(greenPin, 0);
        analogWrite(bluePin, 0);
        Serial.println("TripleLed was disabled");
    } else {
        ledEnabled = true;
        Serial.println("TripleLed was enabled");
    }
}

void TripleLed::update(uint8_t redPart, uint8_t greenPart, uint8_t bluePart) const {
    if (ledEnabled == false) {
        return;
    }
    analogWrite(redPin, redPart);
    analogWrite(greenPin, greenPart);
    analogWrite(bluePin, bluePart);
}

void TripleLed::blinkRed(uint16_t delayMs) const {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(delayMs);
    analogWrite(redPin, 0);
}

void TripleLed::blinkGreen(uint16_t delayMs) const{
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    delay(delayMs);
    analogWrite(greenPin, 0);
}

void TripleLed::blinkBlue(uint16_t delayMs) const{
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
    delay(delayMs);
    analogWrite(bluePin, 0);
}