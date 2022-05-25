//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BUTTERY_H
#define AIR_QUALITY_CLOCK_BUTTERY_H


#include <stdint.h>

#define UPDATE_BUTTERY 75000
#define BUTTERY_MIN 1
#define BUTTERY_MAX 160
#define BUTTERY_MIN_RAW 500
#define BUTTERY_MAX_RAW 1000

class Buttery {
public:
    /**
     * Pin number
     */
    explicit Buttery(uint8_t);

    uint8_t readLevel(uint32_t currentMillis);

private:
    uint8_t _pin;
    uint8_t _level;
};


#endif //AIR_QUALITY_CLOCK_BUTTERY_H
