//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_TRIPLELED_H
#define AIR_QUALITY_CLOCK_TRIPLELED_H

#include <Arduino.h>

class TripleLed {
public:
    TripleLed();

    /**
     * Configures pin's modes
     */
    void initialize(uint8_t red, uint8_t green, uint8_t blue);

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

    void allOff() const;

    /**
     * Enables red color
     */
    void redOn() const;

    void redOff() const;

    /**
     * Enables green color
     */
    void greenOn() const;

    void greenOff() const;

    /**
     * Enables blue color
     */
    void blueOn() const;

    void blueOff() const;

private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
    uint8_t _ledEnabled;
};

#endif //AIR_QUALITY_CLOCK_TRIPLELED_H
