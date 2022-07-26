//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_DS3231_DRAW_H
#define AIR_QUALITY_CLOCK_DS3231_DRAW_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define DS3231_DRAW_DELAY_MS 60000
#define DS3231_DRAW_DATE_TEXT_SIZE 2
#define DS3231_DRAW_TIME_TEXT_SIZE 3
#define DS3231_DRAW_DATETIME_COLOR SCREEN_COLOR_WHITE

#define DS3231_DRAW_DATE_X 20
#define DS3231_DRAW_DATE_Y 7

#define DS3231_DRAW_TIME_X 35
#define DS3231_DRAW_TIME_Y 28


namespace ds3231 {
    void draw();
}

#endif //AIR_QUALITY_CLOCK_DS3231_DRAW_H
