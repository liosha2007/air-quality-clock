//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BATTERY_H
#define AIR_QUALITY_CLOCK_BATTERY_H

#include <stdint.h>

#define BUTTERY_MIN 1
#define BUTTERY_MAX 160
#define BUTTERY_MIN_RAW 1
#define BUTTERY_MAX_RAW 250

class Battery {
public:
    /**
     * Pin number
     */
    explicit Battery();

    void init(uint8_t);

    uint8_t readLevel();

private:
    uint8_t _pin;
    int16_t _level;

    static uint8_t displayableLevel(int16_t level);
};

#endif //AIR_QUALITY_CLOCK_BATTERY_H