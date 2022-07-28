//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BATTERY_H
#define AIR_QUALITY_CLOCK_BATTERY_H

#include <stdint.h>

#define BUTTERY_MIN_RAW 740
#define BUTTERY_MAX_RAW 935

class Battery {
public:
    /**
     * Pin number
     */
    explicit Battery();

    void init(uint8_t);

    uint8_t readLevel(uint8_t min, uint8_t max) const;

private:
    uint8_t _pin;
};

#endif //AIR_QUALITY_CLOCK_BATTERY_H