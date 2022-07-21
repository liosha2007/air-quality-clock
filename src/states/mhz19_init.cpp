//
// Created by liosha on 20.07.2022.
//

#include "states/mhz19_init.h"

namespace mhz19_init {

    enum : uint8_t {
        DrawStage = 1, TryFirst, TrySecond, TryThird
    } nextState = DrawStage;

    static uint32_t capturedTime = 0;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");
                screen.drawProgress(LoadingProgress::STAGE_1);
                capturedTime = millis();
                nextState = TryFirst;
                eventBuffer.push(Event::InitMHZ19);
                break;
            case TryFirst:
                Serial.println("TryFirst");
                if (millis() - capturedTime < 10) {
                    eventBuffer.push(Event::InitMHZ19);
                } else {
                    if (mhz19.init(MHZ19B_TX, MHZ19B_RX)) {
                        screen.drawProgressOk();
                        finishCallback();
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TrySecond;
                        eventBuffer.push(Event::InitMHZ19);
                    }
                }
                break;
            case TrySecond:
                Serial.println("TrySecond");
                if (millis() - capturedTime < 100) {
                    eventBuffer.push(Event::InitMHZ19);
                } else {
                    if (mhz19.init(MHZ19B_TX, MHZ19B_RX)) {
                        screen.drawProgressOk();
                        finishCallback();
                    } else {
                        screen.drawProgressDot();
                        capturedTime = millis();
                        nextState = TryThird;
                        eventBuffer.push(Event::InitMHZ19);
                    }
                }
                break;
            case TryThird:
                Serial.println("TryThird");
                if (millis() - capturedTime < 100) {
                    eventBuffer.push(Event::InitMHZ19);
                } else {
                    if (mhz19.init(MHZ19B_TX, MHZ19B_RX)) {
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