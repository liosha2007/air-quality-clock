//
// Created by liosha on 21.07.2022.
//

#include "states/ccs811/ccs811_draw.h"

namespace ccs811 {

    enum : uint8_t {
        Measure = 1, Draw, Wait
    } nextState = Measure;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Measure:
                if (it.start(CCS811_MODE_60SEC)) {
                    nextState = Draw;
                }
                eventBuffer.push(Event::DrawCCS811);
                break;
            case Draw: {
                Serial.println("Draw");

                uint16_t eco2, etvoc, errstat, raw;
                it.read(&eco2, &etvoc, &errstat, &raw);
//                st7735.drawTVOC(tvoc);

//                if (errstat == CCS811_ERRSTAT_OK_NODATA) {
//                    Serial.println("CCS811: waiting for (new) data");
//                } else if (errstat & CCS811_ERRSTAT_I2CFAIL) {
//                    Serial.println("CCS811: I2C error");
//                } else {
//                    Serial.print("CCS811: errstat=");
//                    Serial.print(errstat, HEX);
//                    Serial.print("=");
//                    Serial.println(it.errstat_str(errstat));
//                }

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

