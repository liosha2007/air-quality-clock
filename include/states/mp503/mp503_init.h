//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_MP503_INIT_H
#define AIR_QUALITY_CLOCK_MP503_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define SCREEN_MP503_INIT_MAX_TRY_COUNT 5

#define MP503_INIT_X 3
#define MP503_INIT_Y (DS3231_INIT_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)
#define MP503_INIT_WIDTH 100
#define MP503_INIT_HEIGHT 40

#define MP503_INIT_TEXT_SIZE 1
#define MP503_INIT_CURSOR_X 3
#define MP503_INIT_CURSOR_Y (DS3231_INIT_CURSOR_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)

namespace mp503 {
    void printTextOnDisplay(const char *, uint16_t textColor);
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_MP503_INIT_H
