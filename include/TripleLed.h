//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_TRIPLELED_H
#define AIR_QUALITY_CLOCK_TRIPLELED_H

#include <Arduino.h>

class TripleLed {
public:
    TripleLed(uint8_t, uint8_t, uint8_t);

    /**
     * Configures pin's modes
     */
    void initialize() const;

    /**
     * Disables or enables the led
     */
    void toggle();

    /**
     * Changes color of triple led
     * If led is disabled - does nothing
     * @param redPart red part of color, 0..255
     * @param greenPart green part of color, 0..255
     * @param bluePart blue part of color, 0..255
     */
    void update(uint8_t redPart, uint8_t greenPart, uint8_t bluePart) const;

    /**
     * Enables red color, sleeps for 500ms and disables led.
     */
    void blinkRed(uint16_t delayMs = 500) const;

    /**
     * Enables green color, sleeps for 500ms and disables led.
     */
    void blinkGreen(uint16_t delayMs = 500) const;

    /**
     * Enables blue color, sleeps for 500ms and disables led.
     */
    void blinkBlue(uint16_t delayMs = 500) const;

private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;
    uint8_t ledEnabled;
};

#endif //AIR_QUALITY_CLOCK_TRIPLELED_H
