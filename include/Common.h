//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_COMMON_H
#define AIR_QUALITY_CLOCK_COMMON_H

#include <stdint-gcc.h>

enum class Event : uint8_t {
    InitLed = 1,
    InitScreen,
    InitBeep,
    InitBattery,  DrawBattery,
    CleanScreen,
    InitMHZ19,    DrawMHZ19,
    InitBME280,   DrawBME280,
    InitDS3231,   DrawDateTime,
    InitMP503,    DrawMP503,
    InitCCS811,   DrawCCS811
};

enum class State : uint8_t {
    Init = 1,
    Measure,
    PreDraw, // Clean screen, ect.
    Draw,
    Delay
};

#endif //AIR_QUALITY_CLOCK_COMMON_H
