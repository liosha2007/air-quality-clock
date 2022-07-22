//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_CCS811_INIT_H
#define AIR_QUALITY_CLOCK_CCS811_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define INIT_MAX_TRY_COUNT 5

namespace ccs811_init {
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_CCS811_INIT_H
