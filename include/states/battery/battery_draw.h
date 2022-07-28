//
// Created by liosha on 26.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_BATTERY_DRAW_H
#define AIR_QUALITY_CLOCK_BATTERY_DRAW_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define BATTERY_DRAW_DELAY_MS 60000
#define BATTERY_DRAW_X 1
#define BATTERY_DRAW_Y 1
#define BATTERY_DRAW_W 160
#define BATTERY_DRAW_H 3

#define BATTERY_DRAW_COLOR ST7735_MAGENTA

namespace battery {
    void draw();
}

#endif //AIR_QUALITY_CLOCK_BATTERY_DRAW_H
