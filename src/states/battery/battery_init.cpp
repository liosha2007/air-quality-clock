//
// Created by liosha on 20.07.2022.
//
#include "states/battery/battery_init.h"

namespace battery {

    void init(void (*finishCallback)()) {
        Serial.print("..");
        Serial.println("Init");

        it.init(PIN_BUTTERY_LEVEL);

        finishCallback();
    }
}