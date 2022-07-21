//
// Created by liosha on 19.07.2022.
//

#include "states/screen_init.h"

namespace screen_init {
    enum : uint8_t {
        Init = 1, DrawLogo, KeepLogo
    } nextState = Init;

    static uint32_t capturedTime = 0;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case Init:
                Serial.println("Init");
                screen.initialize();
                nextState = DrawLogo;
                eventBuffer.push(Event::InitScreen);
                break;
            case DrawLogo:
                Serial.println("DrawLogo");
                screen.drawLogo();
                capturedTime = millis();
                nextState = KeepLogo;
                eventBuffer.push(Event::InitScreen);
                break;
            case KeepLogo:
                Serial.println("KeepLogo");
                if (millis() - capturedTime < 1000) { // KeepLogo
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