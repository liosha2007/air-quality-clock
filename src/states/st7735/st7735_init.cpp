//
// Created by liosha on 19.07.2022.
//

#include "states/st7735/st7735_init.h"

namespace st7735 {
    static State nextState = State::Init;

    static uint32_t capturedTime = 0;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case State::Init:
                Serial.println("Init");

                it.initR(INITR_BLACKTAB);
                it.setRotation(135);
                it.setFont();
                it.enableDisplay(false);

                nextState = State::Draw;
                eventBuffer.push(Event::InitScreen);
                break;
            case State::Draw:
                Serial.println("DrawLogo");

                it.enableDisplay(true);
                it.fillScreen(SCREEN_BACKGROUND);

                // region Draw logo
                it.setTextColor(SCREEN_COLOR_GREEN);
                it.setCursor(SCREEN_LOGO_X, SCREEN_LOGO_Y);
                it.setTextSize(SCREEN_LOGO_TEXT_SIZE);
                it.println("by liosha");
                // endregion

                capturedTime = millis();
                nextState = State::Delay;
                eventBuffer.push(Event::InitScreen);
                break;
            case State::Delay:
                Serial.println("KeepLogo");
                if (millis() - capturedTime < 500) { // KeepLogo
                    eventBuffer.push(Event::InitScreen);
                } else {
                    finishCallback();
                }
                break;
            default:
                Serial.println("__UNKNOWN__");
                finishCallback();
                break;
        }
    }
}