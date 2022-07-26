//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_DS3231_INIT_H
#define AIR_QUALITY_CLOCK_DS3231_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define SCREEN_DS3231_INIT_MAX_TRY_COUNT 5

#define DS3231_INIT_X 10
#define DS3231_INIT_Y (BME280_INIT_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)
#define DS3231_INIT_WIDTH 100
#define DS3231_INIT_HEIGHT 40

#define DS3231_INIT_TEXT_SIZE 1
#define DS3231_INIT_CURSOR_X 3
#define DS3231_INIT_CURSOR_Y (BME280_INIT_CURSOR_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)

namespace ds3231 {
    void printTextOnDisplay(const char *, uint16_t textColor);
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_DS3231_INIT_H
