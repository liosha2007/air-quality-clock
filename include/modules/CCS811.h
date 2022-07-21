//
// Created by liosha on 24.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_CCS811_H
#define AIR_QUALITY_CLOCK_CCS811_H

#include "Keyestudio_CCS811.h"

class CCS811 {
public:
    /**
     * Pin number
     */
    explicit CCS811();

    /**
     * Initializes pins
     */
    bool init();

    uint16_t readCo2();

    uint16_t readTvoc();

private:

    Keyestudio_CCS811 _ccs;
};


#endif //AIR_QUALITY_CLOCK_CCS811_H
