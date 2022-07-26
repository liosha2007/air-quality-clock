//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_ST7735_INIT_H
#define AIR_QUALITY_CLOCK_ST7735_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define SCREEN_LOGO_X 25
#define SCREEN_LOGO_Y 50
#define SCREEN_LOGO_TEXT_SIZE 2

namespace st7735 {
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_ST7735_INIT_H
