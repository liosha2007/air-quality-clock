//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_DS3231_INIT_H
#define AIR_QUALITY_CLOCK_DS3231_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

namespace ds3231_init {
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_DS3231_INIT_H
