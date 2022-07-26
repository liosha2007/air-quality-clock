//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_GLOBALS_H
#define AIR_QUALITY_CLOCK_GLOBALS_H

#include "EventSystem.h"

#include "modules/TripleLed.h"
#include "Adafruit_ST7735.h"
#include "modules/Battery.h"
#include "Mhz19.h"
#include "DS3231.h"
#include <BlueDot_BME280.h>
#include "modules/MP503.h"
#include "ccs811.h"

//static volatile State currentState = State::Idle;

extern CycleBuffer<Event> eventBuffer;

namespace led {
    extern TripleLed it;
}
namespace st7735 {
    extern Adafruit_ST7735 it;
}
namespace battery {
    extern Battery it;
}
namespace mhz19 {
    extern Mhz19 it;
}
namespace ds3231 {
    extern DS3231 it;
}
namespace bme280 {
    extern BlueDot_BME280 it;
}
namespace mp503 {
    extern MP503 it;
}
namespace ccs811 {
    extern CCS811 it;
}

typedef void (*NoParamsCallback)();

#define SCREEN_FONT_SIZE_1_LINE_HEIGHT 12

#define SCREEN_BACKGROUND 0x0000
#define SCREEN_COLOR_WHITE ST7735_WHITE
#define SCREEN_COLOR_GREEN ST7735_GREEN
#define SCREEN_COLOR_GREENYELLOW 0xAFE5
#define SCREEN_COLOR_YELLOW ST7735_YELLOW
#define SCREEN_COLOR_ORANGE ST7735_ORANGE
#define SCREEN_COLOR_RED 0xF800


// endregion

#endif //AIR_QUALITY_CLOCK_GLOBALS_H
