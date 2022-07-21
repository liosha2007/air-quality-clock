//
// Created by liosha on 21.07.2022.
//

#include "states/bme280_draw.h"

namespace bme280_draw {

    enum : uint8_t {
        Draw = 1, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Draw: {
                Serial.println("Draw");

                bme280.takeMeasurement();
                float temperature = bme280.readTemperature();
                uint16_t pressure = bme280.readPressure();
                uint8_t humidity = bme280.readHumidity();

                screen.drawTemperature(temperature);
                screen.drawPressure(pressure);
                screen.drawHumidity(humidity);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_BME280_DELAY_MS) {
                    eventBuffer.push(Event::DrawMHZ19);
                } else  {
                    nextState = Draw;
                    eventBuffer.push(Event::DrawMHZ19);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}

