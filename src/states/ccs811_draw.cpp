//
// Created by liosha on 21.07.2022.
//

#include "states/ccs811_draw.h"

namespace ccs811_draw {

    enum : uint8_t {
        Draw = 1, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Draw: {
                Serial.println("Draw");

                uint16_t tvoc = ccs811.readTvoc();
                screen.drawTVOC(tvoc);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawCCS811);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_CCS811_DELAY_MS) {
                    eventBuffer.push(Event::DrawCCS811);
                } else {
                    nextState = Draw;
                    eventBuffer.push(Event::DrawCCS811);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}

