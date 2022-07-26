//
// Created by liosha on 20.07.2022.
//
#include "states/bme280/bme280_init.h"

namespace bme280 {

    static State nextState = State::Draw;

    static uint32_t capturedTime = 0;
    static uint8_t tryInitCount = 1;

    void printTextOnDisplay(const char *text, uint16_t textColor = SCREEN_COLOR_GREEN) {
        st7735::it.setTextSize(BME280_INIT_TEXT_SIZE);
        st7735::it.setTextColor(textColor);
        st7735::it.print(text);
    }

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case State::Draw:
                Serial.println("DrawStage");

                st7735::it.setCursor(BME280_INIT_CURSOR_X, BME280_INIT_CURSOR_Y);
                printTextOnDisplay("BME280...");

                capturedTime = millis();
                nextState = State::Init;
                eventBuffer.push(Event::InitBME280);
                break;
            case State::Init:
                Serial.println("TryInit");
                if (millis() - capturedTime < tryInitCount * 100) { // Pause 100..200..300..
                    eventBuffer.push(Event::InitBME280);
                } else {
                    it.parameter.communication = 0;                    //I2C
                    it.parameter.I2CAddress = 0x76;                    //I2C Address
                    it.parameter.sensorMode = 0b01;                    //Setup Sensor mode
                    it.parameter.IIRfilter = 0b100;                   //IIR Filter
                    it.parameter.humidOversampling = 0b100;            //Humidity Oversampling
                    it.parameter.tempOversampling = 0b100;              //Temperature Oversampling
                    it.parameter.pressOversampling = 0b100;             //Pressure Oversampling
                    it.parameter.pressureSeaLevel = 1013;
                    it.parameter.tempOutsideCelsius = 15; // Default 15
//                    it.parameter.tempOutsideFahrenheit = 59;

                    if (it.init() == 0x60) {
                        printTextOnDisplay(" OK");
                        finishCallback();
                    } else if (tryInitCount == SCREEN_BME280_INIT_MAX_TRY_COUNT) {
                        printTextOnDisplay(" FAIL", SCREEN_COLOR_RED);
                        finishCallback();
                    } else {
                        printTextOnDisplay(".");
                        tryInitCount++;
                        capturedTime = millis();
                        eventBuffer.push(Event::InitBME280);
                    }
                }
                break;
            default:
                Serial.println("__UNKNOWN__");
                finishCallback();
                break;
        }
    }
}