//
// Created by liosha on 21.07.2022.
//

#include "states/mp503/mp503_draw.h"

namespace mp503 {

    enum : uint8_t {
        Draw = 1, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case Draw: {
                Serial.println("Draw");

                uint8_t pollution = it.readPollution();
                if (pollution == MP503::HEAVY_POLLUTION_AIR) {
//                    st7735.drawPollution(8, 8);
                } else if (pollution == MP503::MIDDLE_POLLUTION_AIR) {
//                    st7735.drawPollution(4, 8);
                } else if (pollution == MP503::SLIGHT_POLLUTION_AIR) {
//                    st7735.drawPollution(2, 8);
                } else if (pollution == MP503::CLEAN_AIR) {
//                    st7735.drawPollution(1, 4);
                }

//                tft.fillRect(POLLUTION_X, POLLUTION_Y, POLLUTION_W, POLLUTION_H, ST7735_BLACK);
//                tft.drawRect(POLLUTION_X, POLLUTION_Y, POLLUTION_W, POLLUTION_H, ST7735_WHITE);
//
//                uint16_t color;
//                uint16_t mapValue;
//                if (maximum / value == maximum / 1) {
//                    color = ST7735_GREEN;
//                    mapValue = 1;
//                } else if (maximum / value == maximum / 2) {
//                    color = ST7735_YELLOW;
//                    mapValue = 2;
//                } else if (maximum / value == maximum / 4) {
//                    color = ST7735_ORANGE;
//                    mapValue = 3;
//                } else { // maximum / 8
//                    color = ST7735_RED;
//                    mapValue = 4;
//                }
//
//                tft.setCursor(POLLUTION_X + 3, POLLUTION_Y - 10);
//                tft.setTextColor(color);
//                tft.setTextSize(1);
//                tft.setTextFont(1);
//                tft.print(String("pollution"));
//
//                uint8_t width = map(mapValue, 1, 4, POLLUTION_W / 4, POLLUTION_W - 2);
//                tft.fillRect(POLLUTION_X + 1, POLLUTION_Y + 1, width, POLLUTION_H - 2, color);




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
