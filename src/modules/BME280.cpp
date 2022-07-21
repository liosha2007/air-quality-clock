//
// Created by liosha on 23.05.2022.
//

#include "modules/BME280.h"

BME280::BME280() : _bme(Adafruit_BME280()) {
}

bool BME280::init() {
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
    return false;
}

void BME280::takeMeasurement() {
    _bme.takeForcedMeasurement();
}

float BME280::readTemperature() {
    float temperature = _bme.readTemperature() - TEMPERATURE_CALIBRATION;

    Serial.print("BME280: temperature = ");
    Serial.println(temperature);

    return /*roundTemperatureQuality(*/temperature/*)*/;
}

uint8_t BME280::readHumidity() {
    float humidity = _bme.readHumidity() - HUMIDITY_CALIBRATION;

    Serial.print("BME280: humidity = ");
    Serial.println(humidity);

    return roundHumidityQuality(humidity);
}

uint16_t BME280::readPressure() {
    float pressure = _bme.readPressure() * 0.00750062f;

    Serial.print("BME280 pressure = ");
    Serial.println(pressure);

    return roundPressureQuality(pressure);
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
