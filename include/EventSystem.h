//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_EVENTSYSTEM_H
#define AIR_QUALITY_CLOCK_EVENTSYSTEM_H

#include <stdint-gcc.h>

#include "CycleBuffer.h"

#include "states/led/led_init.h"
#include "states/st7735/st7735_init.h"
#include "states/st7735/st7735_clean.h"
#include "states/battery/battery_init.h"
#include "states/battery/battery_draw.h"
#include "states/mhz19/mhz19_init.h"
#include "states/bme280/bme280_init.h"
#include "states/ds3231/ds3231_init.h"
#include "states/mp503/mp503_init.h"
#include "states/ccs811/ccs811_init.h"
#include "states/ds3231/ds3231_draw.h"
#include "states/mhz19/mhz19_draw.h"
#include "states/bme280/bme280_draw.h"
#include "states/mp503/mp503_draw.h"
#include "states/ccs811/ccs811_draw.h"

#define EVENT_BUFFER_SIZE 8

void dispatchEvent(Event event);

#endif //AIR_QUALITY_CLOCK_EVENTSYSTEM_H
