//
// Created by liosha on 20.07.2022.
//
#include "states/bme280_init.h"

namespace bme280_init {

    enum : uint8_t {
        DrawStage = 1, TryFirst, TrySecond, TryThird
    } nextState = DrawStage;

    static uint32_t capturedTime = 0;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");
                screen.drawProgress(LoadingProgress::STAGE_2);
                capturedTime = millis();
                nextState = TryFirst;
                eventBuffer.push(Event::InitBME280);
                break;
            case TryFirst:
                Serial.println("TryInit");
                if (millis() - capturedTime < 10) {
                    eventBuffer.push(Event::InitBME280);
                } else {
                    if (bme280.init()) {
                        screen.drawProgressOk();
                        finishCallback();
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TrySecond;
                        eventBuffer.push(Event::InitBME280);
                    }
                }
                break;
            case TrySecond:
                Serial.println("TrySecond");
                if (millis() - capturedTime < 100) {
                    eventBuffer.push(Event::InitBME280);
                } else {
                    if (bme280.init()) {
                        screen.drawProgressOk();
                        finishCallback();
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TryThird;
                        eventBuffer.push(Event::InitBME280);
                    }
                }
                break;
            case TryThird:
                Serial.println("TryThird");
                if (millis() - capturedTime < 100) { // KeepLogo
                    eventBuffer.push(Event::InitBME280);
                } else {
                    if (bme280.init()) {
                        screen.drawProgressOk();
                    } else {
                        screen.drawProgressFail();
                    }
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