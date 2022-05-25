//
// Created by liosha on 24.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_CCS811_H
#define AIR_QUALITY_CLOCK_CCS811_H

#include <Keyestudio_CCS811.h>

#define UPDATE_CCS811 90000

class CCS811 {
public:
    /**
     * Pin number
     */
    explicit CCS811();

    /**
     * Initializes pins
     */
    bool initialize(uint8_t triesCount, void (&)(uint8_t));

    uint16_t readCo2(uint32_t currentMillis);

    uint16_t readTvoc(uint32_t currentMillis);

private:
    void updateValues();

    Keyestudio_CCS811 _ccs;
    uint16_t _co2;
    uint16_t _tvoc;
};


#endif //AIR_QUALITY_CLOCK_CCS811_H
