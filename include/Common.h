//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_COMMON_H
#define AIR_QUALITY_CLOCK_COMMON_H

#include <stdint-gcc.h>

enum class Event : uint8_t {
    InitLed = 1, InitBeep,
    InitScreen,
    InitBattery, DrawBattery,
    CleanScreen,
    InitMHZ19,    DrawMHZ19,
    InitBME280,    DrawBME280,
    InitDS3231,    DrawDateTime,
    InitMP503,    DrawMP503,
    InitCCS811,    DrawCCS811





};

const char *eventToString(Event event);

enum class State : uint8_t {
    Idle, InitScreen, InitDS3231
};

#endif //AIR_QUALITY_CLOCK_COMMON_H
