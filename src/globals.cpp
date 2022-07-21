//
// Created by liosha on 19.07.2022.
//

#include "globals.h"

CycleBuffer<Event> eventBuffer(EVENT_BUFFER_SIZE);

TripleLed led;
Screen screen;
Battery battery;
MHZ19 mhz19;
DS3231 ds3231;
BME280 bme280;
MP503 mp503;
CCS811 ccs811;