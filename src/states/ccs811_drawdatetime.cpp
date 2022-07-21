//
// Created by liosha on 20.07.2022.
//

#include "states/ccs811_drawdatetime.h"

namespace ccs811_drawdatetime {

//    enum : uint8_t {
//        DrawStage = 1, TryFirst, TrySecond, TryThird
//    } nextState = DrawStage;

//    static uint32_t capturedTime = 0;

    void draw() {
//        Serial.print("..");
//        switch (nextState) {
//            case DrawStage:
//                Serial.println("DrawStage");
//                screen.drawProgress(LoadingProgress::STAGE_5);
//                capturedTime = millis();
//                nextState = TryFirst;
//                eventBuffer.push(Event::InitCCS811);
//                break;
//            case TryFirst:
//                Serial.println("TryFirst");
//                if (millis() - capturedTime < 100) {
//                    eventBuffer.push(Event::InitCCS811);
//                } else {
//                    if (ccs811.init()) {
//                        screen.drawProgressOk();
////                        eventBuffer.push(Event::);
//                    } else {
////                        screen.drawProgressDot(); // Bug - display stops drawing anything
//                        capturedTime = millis();
//                        nextState = TrySecond;
//                        eventBuffer.push(Event::InitCCS811);
//                    }
//                }
//                break;
//            case TrySecond:
//                Serial.println("TrySecond");
//                if (millis() - capturedTime < 100) {
//                    eventBuffer.push(Event::InitCCS811);
//                } else {
//                    if (ccs811.init()) {
//                        screen.drawProgressOk();
////                        eventBuffer.push(Event::);
//                    } else {
////                        screen.drawProgressDot(); // Bug - display stops drawing anything
//                        capturedTime = millis();
//                        nextState = TryThird;
//                        eventBuffer.push(Event::InitCCS811);
//                    }
//                }
//                break;
//            case TryThird:
//                Serial.println("TryThird");
//                if (millis() - capturedTime < 100) {
//                    eventBuffer.push(Event::InitCCS811);
//                } else {
//                    if (ccs811.init()) {
//                        screen.drawProgressOk();
//                    } else {
//                        screen.drawProgressFail();
//                    }
////                    eventBuffer.push(Event::);
//                }
//                break;
//            default:
//                Serial.println("__UNKNOWN__");
//                break;
//        }
    }
}

