//
// Created by liosha on 20.07.2022.
//
#include "states/battery/battery_init.h"

namespace battery {

    void init(void (*finishCallback)()) {
        IF_DEBUG(Serial.print("..");)
        IF_DEBUG(Serial.println("Init");)

        it.init(PIN_BUTTERY_LEVEL);

        finishCallback();
    }
}