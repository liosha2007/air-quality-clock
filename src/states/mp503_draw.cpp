//
// Created by liosha on 21.07.2022.
//

#include "states/mp503_draw.h"

namespace mp503_draw {

    enum : uint8_t {
        Draw = 1, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Draw: {
                Serial.println("Draw");

                uint8_t pollution = mp503.readPollution();
                if (pollution == MP503::HEAVY_POLLUTION_AIR) {
                    screen.drawPollution(8, 8);
                } else if (pollution == MP503::MIDDLE_POLLUTION_AIR) {
                    screen.drawPollution(4, 8);
                } else if (pollution == MP503::SLIGHT_POLLUTION_AIR) {
                    screen.drawPollution(2, 8);
                } else if (pollution == MP503::CLEAN_AIR) {
                    screen.drawPollution(1, 4);
                }

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawMP503);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < DRAW_MP503_DELAY_MS) {
                    eventBuffer.push(Event::DrawMP503);
                } else {
                    nextState = Draw;
                    eventBuffer.push(Event::DrawMP503);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}
