//
// Created by liosha on 20.07.2022.
//
#include "states/battery/battery_init.h"

namespace battery {

    enum : uint8_t {
        Init = 1
    } nextState = Init;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case Init:
                Serial.println("Init");

                it.init(PIN_BUTTERY_LEVEL);

                break;
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}