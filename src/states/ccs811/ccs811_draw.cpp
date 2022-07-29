//
// Created by liosha on 21.07.2022.
//

#include "states/ccs811/ccs811_draw.h"

namespace ccs811 {

    static State nextState = State::Measure;

    static uint32_t capturedTime = 0;

    void draw() {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::Measure:
                if (it.start(CCS811_MODE_60SEC)) {
                    nextState = State::Draw;
                }
                eventBuffer.push(Event::DrawCCS811);
                break;
            case State::Draw: {
                IF_DEBUG(Serial.println("Draw");)

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
                nextState = State::Delay;
                eventBuffer.push(Event::DrawCCS811);
                break;
            }
            case State::Delay: {
                IF_DEBUG(Serial.println("Wait");)
                if (millis() - capturedTime < CCS811_DRAW_DELAY_MS) {
                    eventBuffer.push(Event::DrawCCS811);
                } else {
                    nextState = State::Measure;
                    eventBuffer.push(Event::DrawCCS811);
                }
                break;
            }
            default:
                IF_DEBUG(Serial.println("__UNKNOWN__");)
                break;
        }
    }
}

