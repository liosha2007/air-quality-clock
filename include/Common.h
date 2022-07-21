//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_COMMON_H
#define AIR_QUALITY_CLOCK_COMMON_H

#include <stdint-gcc.h>

enum class Event : uint8_t {
    InitLed = 1, InitBeep, InitBattery,
    InitScreen,
    InitMHZ19,
    InitBME280,
    InitDS3231,
    InitMP503,
    InitCCS811,
    DrawDateTime,
    DrawMHZ19,
    DrawBME280,
    DrawMP503,
    DrawCCS811
};

const char *eventToString(Event event);

enum class State : uint8_t {
    Idle, InitScreen, InitDS3231
};

#endif //AIR_QUALITY_CLOCK_COMMON_H
