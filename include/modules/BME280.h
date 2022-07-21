//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BME280_H
#define AIR_QUALITY_CLOCK_BME280_H

#include <stdint.h>

//#define SEALEVELPRESSURE_HPA (1013.25)
#define TEMPERATURE_CALIBRATION 5
#define HUMIDITY_CALIBRATION (-5)

#include "Adafruit_BME280.h"

/**
 * Temperature, humidity and pressure
 */
class BME280 {
public:
    /**
     * Pin number
     */
    explicit BME280();

    /**
     * Initializes pins
     */
    bool init();

    void takeMeasurement();

    float readTemperature();

    uint8_t readHumidity();

    uint16_t readPressure();

private:

    static uint16_t roundPressureQuality(float);

    static uint8_t roundHumidityQuality(float);

    static float roundTemperatureQuality(float);

    Adafruit_BME280 _bme;
};


#endif //AIR_QUALITY_CLOCK_BME280_H
