//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_MHZ19_INIT_H
#define AIR_QUALITY_CLOCK_MHZ19_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define MHZ19_SERIAL_SPEED 9600

#define MHZ19_INIT_X 3
#define MHZ19_INIT_Y 3
#define MHZ19_INIT_WIDTH 100
#define MHZ19_INIT_HEIGHT 40

#define MHZ19_INIT_TEXT_SIZE 1
#define MHZ19_INIT_CURSOR_X 3
#define MHZ19_INIT_CURSOR_Y 3

namespace mhz19 {
    void printTextOnDisplay(const char *, uint16_t textColor);
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_MHZ19_INIT_H
