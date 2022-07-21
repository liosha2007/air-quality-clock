//
// Created by liosha on 19.07.2022.
//
#include "states/ds3231_init.h"

namespace ds3231_init {

    enum : uint8_t {
        DrawStage = 1, TryFirst, TrySecond, TryThird
    } nextState = DrawStage;

    static uint32_t capturedTime = 0;

    void init() {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");
                screen.drawProgress(LoadingProgress::STAGE_3);
                capturedTime = millis();
                nextState = TryFirst;
                eventBuffer.push(Event::InitDS3231);
                break;
            case TryFirst:
                Serial.println("TryFirst");
                if (millis() - capturedTime < 100) { // KeepLogo
                    eventBuffer.push(Event::InitDS3231);
                } else {
                    if (ds3231.init()) {
                        screen.drawProgressOk();
                        eventBuffer.push(Event::InitDS3231Finish);
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TrySecond;
                        eventBuffer.push(Event::InitDS3231);
                    }
                }
                break;
            case TrySecond:
                Serial.println("TrySecond");
                if (millis() - capturedTime < 100) { // KeepLogo
                    eventBuffer.push(Event::InitDS3231);
                } else {
                    if (ds3231.init()) {
                        screen.drawProgressOk();
                        eventBuffer.push(Event::InitDS3231Finish);
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TryThird;
                        eventBuffer.push(Event::InitDS3231);
                    }
                }
                break;
            case TryThird:
                Serial.println("TryThird");
                if (millis() - capturedTime < 100) { // KeepLogo
                    eventBuffer.push(Event::InitDS3231);
                } else {
                    if (ds3231.init()) {
                        screen.drawProgressOk();
                    } else {
                        screen.drawProgressFail();
                    }
                    eventBuffer.push(Event::InitDS3231Finish);
                }
                break;
            default:
                Serial.println("__UNKNOWN__");
                eventBuffer.push(Event::InitDS3231Finish);
                break;
        }
    }
}