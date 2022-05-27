//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_BME280_H
#define AIR_QUALITY_CLOCK_BME280_H

#include <stdint.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#include <Adafruit_BME280.h>

#define UPDATE_BME280 60000

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
    bool initialize(uint8_t triesCount, void (&)(uint8_t));

    float readTemperature(uint32_t currentMillis);

    uint8_t readHumidity(uint32_t currentMillis);

    uint16_t readPressure(uint32_t currentMillis);

private:
    void updateValues();

    static uint16_t roundPressureQuality(float);

    static uint8_t roundHumidityQuality(float);

    static float roundTemperatureQuality(float);

    Adafruit_BME280 _bme;
    float _temperature;
    float _humidity;
    float _pressure;
};


#endif //AIR_QUALITY_CLOCK_BME280_H
