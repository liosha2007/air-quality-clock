//
// Created by liosha on 21.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_MHZ19_DRAW_H
#define AIR_QUALITY_CLOCK_MHZ19_DRAW_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define DRAW_MHZ19_DELAY_MS 10000
#define DRAW_MHZ19_LABEL_SIZE 1
#define DRAW_MHZ19_DATA_SIZE 2

#define DRAW_MHZ19_DRAW_DATA_X 112
#define DRAW_MHZ19_DRAW_DATA_Y 85

#define DRAW_MHZ19_DRAW_LABEL_X 92
#define DRAW_MHZ19_DRAW_LABEL_Y 85

namespace mhz19 {
    void draw();
}

#endif //AIR_QUALITY_CLOCK_MHZ19_DRAW_H
