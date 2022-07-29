//
// Created by liosha on 20.07.2022.
//

#include "states/mp503/mp503_init.h"

namespace mp503 {

    static State nextState = State::Draw;

    static uint32_t capturedTime = 0;
    static uint8_t tryInitCount = 1;

    void printTextOnDisplay(const char *text, uint16_t textColor = SCREEN_COLOR_GREEN) {
        st7735::it.setTextSize(MP503_INIT_TEXT_SIZE);
        st7735::it.setTextColor(textColor);
        st7735::it.print(text);
    }

    void init(void (*finishCallback)()) {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::Draw:

                st7735::it.setCursor(MP503_INIT_CURSOR_X, MP503_INIT_CURSOR_Y);
                printTextOnDisplay("MP503...");

                capturedTime = millis();
                nextState = State::Init;
                eventBuffer.push(Event::InitMP503);
                break;
            case State::Init:
                IF_DEBUG(Serial.println("TryInit");)
                if (millis() - capturedTime < tryInitCount * 100) { // Pause 100..200..300..
                    eventBuffer.push(Event::InitMP503);
                } else {
                    if (it.init(MP503_A, MP503_B)) {
                        printTextOnDisplay(" OK");
                        finishCallback();
                    } else if (tryInitCount == SCREEN_MP503_INIT_MAX_TRY_COUNT) {
                        printTextOnDisplay(" FAIL", SCREEN_COLOR_RED);
                        finishCallback();
                    } else {
                        printTextOnDisplay(".");
                        tryInitCount++;
                        capturedTime = millis();
                        eventBuffer.push(Event::InitMP503);
                    }
                }
                break;
            default:
                IF_DEBUG(Serial.println("__UNKNOWN__");)
                finishCallback();
                break;
        }
    }
}
