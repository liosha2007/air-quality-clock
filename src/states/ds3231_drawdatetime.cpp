//
// Created by liosha on 20.07.2022.
//

#include "states/ds3231_drawdatetime.h"

namespace ds3231_drawdatetime {

    enum : uint8_t {
        CleanScreen = 1, DrawDots, DrawTime, Wait
    } nextState = CleanScreen;

    static uint32_t capturedTime = 0;
    static bool isShowDots = false;

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case CleanScreen:
                Serial.println("CleanScreen");

                screen.cleanScreen();

                nextState = DrawTime;
                eventBuffer.push(Event::DrawDateTime);
                break;
            case DrawDots:
                Serial.println("DrawDots");

                screen.drawDateTimeSeparator(isShowDots);
                isShowDots = !isShowDots;

                nextState = Wait;
                eventBuffer.push(Event::DrawDateTime);
                break;
            case DrawTime: {
                Serial.println("DrawTime");

                DateTime dateTime = ds3231.readDateTime();
                screen.drawDateTime(dateTime);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawDateTime);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                uint32_t ms = millis();
                uint16_t devLeft = (ms - capturedTime) % 500;
                if (devLeft > 420 && devLeft < 580) {
                    nextState = DrawDots;
                    eventBuffer.push(Event::DrawDateTime);
                } else if (ms - capturedTime < DRAW_TIME_DELAY_MS) {
                    eventBuffer.push(Event::DrawDateTime);
                } else  {
                    nextState = DrawTime;
                    eventBuffer.push(Event::DrawDateTime);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}