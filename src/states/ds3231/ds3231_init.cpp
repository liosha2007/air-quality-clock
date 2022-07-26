//
// Created by liosha on 19.07.2022.
//
#include "states/ds3231/ds3231_init.h"

namespace ds3231 {

    enum : uint8_t {
        DrawStage = 1, TryInit
    } nextState = DrawStage;


    void printTextOnDisplay(const char *text, uint16_t textColor = SCREEN_COLOR_GREEN) {
        st7735::it.setTextSize(DS3231_INIT_TEXT_SIZE);
        st7735::it.setTextColor(textColor);
        st7735::it.print(text);
    }

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");

                st7735::it.setCursor(DS3231_INIT_CURSOR_X, DS3231_INIT_CURSOR_Y);
                printTextOnDisplay("DS3231...");

                nextState = TryInit;
                eventBuffer.push(Event::InitDS3231);
                break;
            case TryInit:
                Serial.println("TryInit");

                Wire.begin();
                printTextOnDisplay(" OK");

                finishCallback();
                break;

            default:
                Serial.println("__UNKNOWN__");
                finishCallback();
                break;
        }
    }
}