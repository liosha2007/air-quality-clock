//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_CCS811_INIT_H
#define AIR_QUALITY_CLOCK_CCS811_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define CCS811_INIT_MAX_TRY_COUNT 5

#define CCS811_INIT_X 3
#define CCS811_INIT_Y (MP503_INIT_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)
#define CCS811_INIT_WIDTH 100
#define CCS811_INIT_HEIGHT 40

#define CCS811_INIT_TEXT_SIZE 1
#define CCS811_INIT_CURSOR_X 3
#define CCS811_INIT_CURSOR_Y (MP503_INIT_CURSOR_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)

namespace ccs811 {
    void printTextOnDisplay(const char *, uint16_t textColor);
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_CCS811_INIT_H
