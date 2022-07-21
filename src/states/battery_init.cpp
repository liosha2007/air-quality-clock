//
// Created by liosha on 20.07.2022.
//
#include "states/battery_init.h"

namespace battery_init {

    enum : uint8_t {
        Init = 1
    } nextState = Init;

    void init() {
        Serial.print("..");
        switch (nextState) {
            case Init:
                Serial.println("Init");

                battery.init(PIN_BUTTERY_LEVEL);

                eventBuffer.push(Event::InitLed);
                break;
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}