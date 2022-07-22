//
// Created by liosha on 19.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_GLOBALS_H
#define AIR_QUALITY_CLOCK_GLOBALS_H

#include "EventSystem.h"
#include "modules/TripleLed.h"
#include "modules/Screen.h"
#include "modules/Battery.h"
#include "modules/MHZ19.h"
#include "modules/DS3231.h"
#include "modules/MP503.h"
#include "modules/BME280.h"
#include "DFRobot_CCS811.h"

//static volatile State currentState = State::Idle;

extern CycleBuffer<Event> eventBuffer;

extern TripleLed led;
extern Screen screen;
extern Battery battery;
extern MHZ19 mhz19;
extern DS3231 ds3231;
extern BME280 bme280;
extern MP503 mp503;
extern DFRobot_CCS811 ccs811;

typedef void (*NoParamsCallback)();

#endif //AIR_QUALITY_CLOCK_GLOBALS_H
