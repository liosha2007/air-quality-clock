//
// Created by liosha on 21.07.2022.
//

#include "states/ccs811_draw.h"

namespace ccs811_draw {

    enum : uint8_t {
        Measure = 1, Draw, Wait
    } nextState = Measure;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Measure:
                if (ccs811.checkDataReady()) {
                    nextState = Draw;
                }
                eventBuffer.push(Event::DrawCCS811);
                break;
            case Draw: {
                Serial.println("Draw");

                uint16_t tvoc = ccs811.getTVOCPPB();
                screen.drawTVOC(tvoc);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawCCS811);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < CCS811_DRAW_DELAY_MS) {
                    eventBuffer.push(Event::DrawCCS811);
                } else {
                    nextState = Measure;
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

