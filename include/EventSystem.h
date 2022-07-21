//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_EVENTSYSTEM_H
#define AIR_QUALITY_CLOCK_EVENTSYSTEM_H

#include <stdint-gcc.h>

#include "CycleBuffer.h"
#include "states/led_init.h"
#include "states/screen_init.h"
#include "states/battery_init.h"
#include "states/mhz19_init.h"
#include "states/bme280_init.h"
#include "states/ds3231_init.h"
#include "states/mp503_init.h"
#include "states/ccs811_init.h"
#include "states/ccs811_drawdatetime.h"

#define EVENT_BUFFER_SIZE 8

typedef void (*NoParamsCallback)();

void idleStateCallback();


void dispatchEvent(Event event);

#endif //AIR_QUALITY_CLOCK_EVENTSYSTEM_H
