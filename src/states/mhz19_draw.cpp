//
// Created by liosha on 21.07.2022.
//

#include "states/mhz19_draw.h"

namespace mhz19_draw {

    enum : uint8_t {
        Draw = 1, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Draw: {
                Serial.println("Draw");

                int16_t  co2 = mhz19.readCo2();
                screen.drawCO2(co2);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawMHZ19);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_MHZ19_DELAY_MS) {
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
