//
// Created by liosha on 19.07.2022.
//

#include "globals.h"

#define ST7735_TFT_CS        A2
#define ST7735_TFT_RST        -1 // Or set to -1 and connect to Arduino RESET pin
#define ST7735_TFT_DC         A1

CycleBuffer<Event> eventBuffer(EVENT_BUFFER_SIZE);

namespace led {
    TripleLed it;
}
namespace st7735 {
    Adafruit_ST7735 it = Adafruit_ST7735(ST7735_TFT_CS, ST7735_TFT_DC, ST7735_TFT_RST);
}
namespace battery {
    Battery it;
}
namespace mhz19 {
    Mhz19 it;
}
namespace ds3231 {
    DS3231 it;
}
namespace bme280 {
    BlueDot_BME280 it;
}
namespace mp503 {
    MP503 it;
}
namespace ccs811 {
    CCS811 it;
}