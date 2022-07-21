//
// Created by liosha on 23.05.2022.
//

#include "modules/BME280.h"

BME280::BME280() {
    _bme = Adafruit_BME280();
    _temperature = 0;
    _humidity = 0;
    _pressure = 0;
}

bool BME280::initialize(uint8_t triesCount, void (&callback)(uint8_t)) {
    uint8_t tryNumber = 0;
    while (tryNumber < triesCount) {
        if (_bme.begin(BME280_ADDRESS)) {
            // Configure BME280
//            _bme.seaLevelForAltitude(, SEALEVELPRESSURE_HPA)
            _bme.setSampling(Adafruit_BME280::MODE_FORCED,
                             Adafruit_BME280::SAMPLING_X1, // Temperature
                             Adafruit_BME280::SAMPLING_X1, // pressure
                             Adafruit_BME280::SAMPLING_X1, // humidity
                             Adafruit_BME280::FILTER_OFF);
            return true;
        }
        callback(tryNumber);
        tryNumber++;
        delay(10);
    }
    return false;
}

float BME280::readTemperature(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_BME280) == 0 || _temperature == 0 /* Initial load */) {
        updateValues();

        Serial.print("BME280: temperature = ");
        Serial.println(_temperature);
    }
    return /*roundTemperatureQuality(*/_temperature/*)*/;
}

uint8_t BME280::readHumidity(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_BME280) == 0 || _humidity == 0 /* Initial load */) {
        updateValues();

        Serial.print("BME280: humidity = ");
        Serial.println(_humidity);
    }
    return roundHumidityQuality(_humidity);
}

uint16_t BME280::readPressure(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_BME280) == 0 || _pressure == 0 /* Initial load */) {
        updateValues();

        Serial.print("BME280 pressure = ");
        Serial.println(_pressure);
    }
    return roundPressureQuality(_pressure);
}

void BME280::updateValues() {
    _bme.takeForcedMeasurement();
    _temperature = _bme.readTemperature() - TEMPERATURE_CALIBRATION;
    _humidity = _bme.readHumidity() - HUMIDITY_CALIBRATION;
    _pressure = _bme.readPressure() * 0.00750062f;
}

uint16_t BME280::roundPressureQuality(float value) {
    return (uint16_t) value;
}

uint8_t BME280::roundHumidityQuality(float value) {
    return (uint8_t) value;
}

float BME280::roundTemperatureQuality(float value) {
    return (((float) ((uint8_t) (value * 10))) / 10);
}