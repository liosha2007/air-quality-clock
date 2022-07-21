//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_BME280_INIT_H
#define AIR_QUALITY_CLOCK_BME280_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

namespace bme280_init {
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_BME280_INIT_H
