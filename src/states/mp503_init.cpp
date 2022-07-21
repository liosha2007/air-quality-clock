//
// Created by liosha on 20.07.2022.
//

#include "states/mp503_init.h"

namespace mp503_init {

    enum : uint8_t {
        DrawStage = 1, TryFirst
    } nextState = DrawStage;

    static uint32_t capturedTime = 0;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");
                screen.drawProgress(LoadingProgress::STAGE_4);
                capturedTime = millis();
                nextState = TryFirst;
                eventBuffer.push(Event::InitMP503);
                break;
            case TryFirst:
                Serial.println("TryFirst");
                if (millis() - capturedTime < 100) {
                    eventBuffer.push(Event::InitMP503);
                } else {
                    if (mp503.init(MP503_A, MP503_B)) {
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
