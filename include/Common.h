//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_COMMON_H
#define AIR_QUALITY_CLOCK_COMMON_H

#include <stdint-gcc.h>

enum class Event : uint8_t {
    InitLed = 1, InitBeep, InitBattery,
    InitScreen, InitScreenFinish,
    InitMHZ19, InitMHZ19Finish,
    InitBME280, InitBME280Finish,
    InitDS3231, InitDS3231Finish,
    InitMP503, InitMP503Finish,
    InitCCS811, InitCCS811Finish,
    DrawDateTime
};

const char *eventToString(Event event);

enum class State : uint8_t {
    Idle, InitScreen, InitDS3231
};

#endif //AIR_QUALITY_CLOCK_COMMON_H
