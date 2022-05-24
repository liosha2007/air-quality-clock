//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_UTILS_H
#define AIR_QUALITY_CLOCK_UTILS_H

#include <Arduino.h>

typedef enum {
    GOOD = (1),
    NORMAL = (2),
    BAD = (3),
    WARNING = (4),
    DANGEROUS = (5)
} Quality;

Quality detectCo2Quality(int16_t);

Quality detectPressureQuality(uint16_t);

Quality detectHumanityQuality(uint8_t);

Quality detectTemperatureQuality(float);

#endif //AIR_QUALITY_CLOCK_UTILS_H
