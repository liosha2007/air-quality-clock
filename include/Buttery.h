//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BUTTERY_H
#define AIR_QUALITY_CLOCK_BUTTERY_H


#include <stdint.h>

#define UPDATE_BUTTERY 15000
#define BUTTERY_MIN 1
#define BUTTERY_MAX 160
#define BUTTERY_MIN_RAW 1
#define BUTTERY_MAX_RAW 250

class Buttery {
public:
    /**
     * Pin number
     */
    explicit Buttery(uint8_t);

    void initialize() const;

    uint8_t readLevel(uint32_t currentMillis);

private:
    uint8_t _pin;
    int16_t _level;

    static uint8_t displayableLevel(int16_t level);
};


#endif //AIR_QUALITY_CLOCK_BUTTERY_H
