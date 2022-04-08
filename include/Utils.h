//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_UTILS_H
#define AIR_QUALITY_CLOCK_UTILS_H

#include <Arduino.h>

uint16_t roundPressureQuality(float);

uint8_t roundHumanityQuality(float);

float roundTemperatureQuality(float);

typedef enum {
    GOOD = (1),
    NORMAL = (2),
    BAD = (3),
    WARNING = (4),
    DANGEROUS = (5)
} Quality;

Quality detectCo2Quality(int16_t);

Quality detectPressureQuality(int16_t);

Quality detectHumanityQuality(uint8_t);

Quality detectTemperatureQuality(float);

#endif //AIR_QUALITY_CLOCK_UTILS_H
