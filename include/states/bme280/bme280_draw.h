//
// Created by liosha on 21.07.2022.
//

#ifndef AIR_QUALITY_CLOCK_BME280_DRAW_H
#define AIR_QUALITY_CLOCK_BME280_DRAW_H

#include "globals.h"
#include "Common.h"
#include "EventSystem.h"

#define DRAW_BME280_DELAY_MS 1000
#define DRAW_BME280_LABEL_SIZE 1
#define DRAW_BME280_DATA_SIZE 2

#define DRAW_BME280_TEMPERATURE_CORRECTION (-4)

#define DRAW_BME280_DRAW_TEMPERATURE_LABEL_X 2
#define DRAW_BME280_DRAW_TEMPERATURE_LABEL_Y 60
#define DRAW_BME280_DRAW_TEMPERATURE_DATA_X (DRAW_BME280_DRAW_TEMPERATURE_LABEL_X + 20)
#define DRAW_BME280_DRAW_TEMPERATURE_DATA_Y DRAW_BME280_DRAW_TEMPERATURE_LABEL_Y

#define DRAW_BME280_DRAW_HUMIDITY_LABEL_X 5
#define DRAW_BME280_DRAW_HUMIDITY_LABEL_Y 85
#define DRAW_BME280_DRAW_HUMIDITY_DATA_X (DRAW_BME280_DRAW_HUMIDITY_LABEL_X - 3)
#define DRAW_BME280_DRAW_HUMIDITY_DATA_Y (DRAW_BME280_DRAW_HUMIDITY_LABEL_Y + 10)
#define DRAW_BME280_DRAW_HUMIDITY_DATA_W 60
#define DRAW_BME280_DRAW_HUMIDITY_DATA_H 8

#define DRAW_BME280_DRAW_PRESSURE_LABEL_X 2
#define DRAW_BME280_DRAW_PRESSURE_LABEL_Y 112
#define DRAW_BME280_DRAW_PRESSURE_DATA_X (DRAW_BME280_DRAW_PRESSURE_LABEL_X + 20)
#define DRAW_BME280_DRAW_PRESSURE_DATA_Y DRAW_BME280_DRAW_PRESSURE_LABEL_Y

namespace bme280 {
    void draw();
    uint16_t getColorDependingOnTemperature(float value);
    uint16_t getColorDependingOnPressure(float value);
    uint16_t getColorDependingOnHumidity(int16_t value);
}

#endif //AIR_QUALITY_CLOCK_BME280_DRAW_H
