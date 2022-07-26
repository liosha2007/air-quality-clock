//
// Created by liosha on 21.07.2022.
//

#include "states/bme280/bme280_draw.h"

namespace bme280 {

    enum : uint8_t {
        CleanArea = 1, Draw, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;
    static char temperatureString[8] = {0};
    static char pressureString[8] = {0};

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case CleanArea:
                Serial.println("CleanArea");

                // Clean temperature
                st7735::it.setCursor(DRAW_BME280_DRAW_TEMPERATURE_DATA_X, DRAW_BME280_DRAW_TEMPERATURE_DATA_Y);
                st7735::it.setTextSize(DRAW_BME280_DATA_SIZE);
                st7735::it.setTextColor(SCREEN_BACKGROUND);
                st7735::it.println(temperatureString);

                // Clean pressure
                st7735::it.setCursor(DRAW_BME280_DRAW_PRESSURE_DATA_X, DRAW_BME280_DRAW_PRESSURE_DATA_Y);
                st7735::it.setTextSize(DRAW_BME280_DATA_SIZE);
                st7735::it.setTextColor(SCREEN_BACKGROUND);
                st7735::it.println(pressureString);

                // Clean humidity
                st7735::it.drawRect(DRAW_BME280_DRAW_HUMIDITY_DATA_X, DRAW_BME280_DRAW_HUMIDITY_DATA_Y,
                                    DRAW_BME280_DRAW_HUMIDITY_DATA_W, DRAW_BME280_DRAW_HUMIDITY_DATA_H, ST7735_WHITE);

                nextState = Draw;
                eventBuffer.push(Event::DrawBME280);
                break;
            case Draw: {
                Serial.println("Draw");

//                it.takeForcedMeasurement();
                // region temperature
                float temperature = it.readTempC();
                st7735::it.setTextSize(DRAW_BME280_DATA_SIZE);
                st7735::it.setTextColor(getColorDependingOnTemperature(temperature));

                st7735::it.setCursor(DRAW_BME280_DRAW_TEMPERATURE_DATA_X, DRAW_BME280_DRAW_TEMPERATURE_DATA_Y);
                sprintf(temperatureString, "%u", (int8_t) temperature);
                st7735::it.println(temperatureString);

                st7735::it.setTextSize(DRAW_BME280_LABEL_SIZE);
                st7735::it.setCursor(DRAW_BME280_DRAW_TEMPERATURE_LABEL_X, DRAW_BME280_DRAW_TEMPERATURE_LABEL_Y);
                st7735::it.println("tmp");
                // endregion

                // region pressure
                float pressure = it.readPressure();
                st7735::it.setTextSize(DRAW_BME280_DATA_SIZE);
                st7735::it.setTextColor(getColorDependingOnPressure(pressure));

                st7735::it.setCursor(DRAW_BME280_DRAW_PRESSURE_DATA_X, DRAW_BME280_DRAW_PRESSURE_DATA_Y);
                sprintf(pressureString, "%u", (uint16_t) pressure);
                st7735::it.println(pressureString);

                st7735::it.setTextSize(DRAW_BME280_LABEL_SIZE);
                st7735::it.setCursor(DRAW_BME280_DRAW_PRESSURE_LABEL_X, DRAW_BME280_DRAW_PRESSURE_LABEL_Y);
                st7735::it.println("prs");
                // endregion

                // region humidity
                float humidity = it.readHumidity();

                uint8_t width = map((long) humidity, 1, 100, DRAW_BME280_DRAW_HUMIDITY_DATA_W / 4,
                                    DRAW_BME280_DRAW_HUMIDITY_DATA_W - 2);
                st7735::it.fillRect(DRAW_BME280_DRAW_HUMIDITY_DATA_X + 1, DRAW_BME280_DRAW_HUMIDITY_DATA_Y + 1, width,
                                    DRAW_BME280_DRAW_HUMIDITY_DATA_H - 2,
                                    getColorDependingOnHumidity((int8_t) humidity));

                st7735::it.setTextSize(DRAW_BME280_LABEL_SIZE);
                st7735::it.setCursor(DRAW_BME280_DRAW_HUMIDITY_LABEL_X, DRAW_BME280_DRAW_HUMIDITY_LABEL_Y);
                st7735::it.println("humidity");
                // endregion

                Serial.print("...temperature: ");
                Serial.print(temperature);
                Serial.print(", pressure: ");
                Serial.print(pressure);
                Serial.print(", humidity: ");
                Serial.println(humidity);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawBME280);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_BME280_DELAY_MS) {
                    eventBuffer.push(Event::DrawBME280);
                } else {
                    nextState = CleanArea;
                    eventBuffer.push(Event::DrawBME280);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }

    uint16_t getColorDependingOnTemperature(float value) {
        // 24 is ok, +-2
        if (value >= 12 && value < 18) {
            return SCREEN_COLOR_ORANGE; // BAD
        } else if (value >= 18 && value < 22) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 22 && value < 27) {
            return SCREEN_COLOR_GREEN; // GOOD
        } else if (value >= 27 && value < 30) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 30 && value < 35) {
            return SCREEN_COLOR_ORANGE; // BAD
        } else {
            return SCREEN_COLOR_RED; // DANGEROUS
        }
    }

    uint16_t getColorDependingOnPressure(float value) {
        // 0m over sea 641 - 760 - 816
        // ZP - 86m over sea, 649 - 768 - 824
        if (value >= 609 && value < 679) {
            return SCREEN_COLOR_ORANGE; //BAD
        } else if (value >= 679 && value < 709) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 709 && value < 739) {
            return SCREEN_COLOR_GREENYELLOW; // NORMAL
        } else if (value >= 739 && value < 797) {
            return SCREEN_COLOR_GREEN;// GOOD
        } else if (value >= 797 && value < 827) {
            return SCREEN_COLOR_GREENYELLOW; // NORMAL
        } else if (value >= 827 && value < 857) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 857 && value < 927) {
            return SCREEN_COLOR_ORANGE; //BAD
        } else {
            return SCREEN_COLOR_RED; // DANGEROUS
        }
    }

    uint16_t getColorDependingOnHumidity(int16_t value) {
        // 40-60 is ok, 25-40 and 60-75 so so
        if (value >= 10 && value < 25) {
            return SCREEN_COLOR_ORANGE; //BAD
        }
        if (value >= 25 && value < 40) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 40 && value <= 60) {
            return SCREEN_COLOR_GREEN;// GOOD
        } else if (value >= 60 && value < 75) {
            return SCREEN_COLOR_YELLOW; // WARNING
        } else if (value >= 75 && value < 90) {
            return SCREEN_COLOR_ORANGE; //BAD
        } else {
            return SCREEN_COLOR_RED; // DANGEROUS
        }
    }
}

