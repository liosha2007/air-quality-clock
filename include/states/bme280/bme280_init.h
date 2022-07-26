//
// Created by liosha on 20.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_BME280_INIT_H
#define AIR_QUALITY_CLOCK_BME280_INIT_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define SCREEN_BME280_INIT_MAX_TRY_COUNT 5

#define BME280_INIT_X 3
#define BME280_INIT_Y  (MHZ19_INIT_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)
#define BME280_INIT_WIDTH 100
#define BME280_INIT_HEIGHT 40

#define BME280_INIT_TEXT_SIZE 1
#define BME280_INIT_CURSOR_X 3
#define BME280_INIT_CURSOR_Y (MHZ19_INIT_CURSOR_Y + SCREEN_FONT_SIZE_1_LINE_HEIGHT)

namespace bme280 {
    void printTextOnDisplay(const char *, uint16_t textColor);
    void init(void (*finishCallback)());
}

#endif //AIR_QUALITY_CLOCK_BME280_INIT_H
