//
// Created by liosha on 26.07.2022.
//

#include "states/battery/battery_draw.h"

namespace battery {

    enum : uint8_t {
        CleanArea = 1, Draw, Wait
    } nextState = Draw;

    static uint32_t capturedTime = 0;
    static char batteryString[8] = {0};

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case CleanArea:
                Serial.println("CleanArea");

                st7735::it.setTextSize(1);
                st7735::it.setTextColor(SCREEN_BACKGROUND);
                st7735::it.setCursor(BATTERY_DRAW_X, BATTERY_DRAW_Y);
                st7735::it.println(batteryString);

                nextState = Draw;
                eventBuffer.push(Event::DrawBattery);
                break;
            case Draw: {
                Serial.println("Draw");


                uint16_t level = analogRead(A7); // raw level
                st7735::it.setTextSize(1);
                st7735::it.setTextColor(ST7735_RED);
                st7735::it.setCursor(BATTERY_DRAW_X, BATTERY_DRAW_Y);
                sprintf(batteryString, "%02d", level);
                st7735::it.println(batteryString);



                break;
            }
            case Wait: {
                Serial.println("Wait");
                if (millis() - capturedTime < BATTERY_DRAW_DELAY_MS) {
                    eventBuffer.push(Event::DrawBattery);
                } else {
                    nextState = CleanArea;
                    eventBuffer.push(Event::DrawBattery);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}