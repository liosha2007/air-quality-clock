//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_BATTERY_INIT_H
#define AIR_QUALITY_CLOCK_BATTERY_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"
#include "Constants.h"

namespace battery {
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_BATTERY_INIT_H
