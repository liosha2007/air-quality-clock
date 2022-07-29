//
// Created by liosha on 26.07.2022.
//

#include "states/battery/battery_draw.h"

namespace battery {

    static State nextState = State::Draw;

    static uint32_t capturedTime = 0;

    void draw() {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::PreDraw:
                IF_DEBUG(Serial.println("CleanArea");)

                st7735::it.fillRect(BATTERY_DRAW_X, BATTERY_DRAW_Y, BATTERY_DRAW_W, BATTERY_DRAW_H, SCREEN_BACKGROUND);

                nextState = State::Draw;
                eventBuffer.push(Event::DrawBattery);
                break;
            case State::Draw: {
                IF_DEBUG(Serial.println("Draw");)

                uint8_t levelWidth = it.readLevel(1, BATTERY_DRAW_W);
                st7735::it.fillRect(BATTERY_DRAW_X, BATTERY_DRAW_Y, levelWidth, BATTERY_DRAW_H, BATTERY_DRAW_COLOR);

                capturedTime = millis();
                nextState = State::Delay;
                eventBuffer.push(Event::DrawBattery);
                break;
            }
            case State::Delay: {
                IF_DEBUG(Serial.println("Wait");)
                if (millis() - capturedTime < BATTERY_DRAW_DELAY_MS) {
                    eventBuffer.push(Event::DrawBattery);
                } else {
                    nextState = State::PreDraw;
                    eventBuffer.push(Event::DrawBattery);
                }
                break;
            }
            default:
                IF_DEBUG(Serial.println("__UNKNOWN__");)
                break;
        }
    }
}