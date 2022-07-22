//
// Created by liosha on 20.07.2022.
//

#include "states/ccs811_init.h"

namespace ccs811_init {

    enum : uint8_t {
        DrawStage = 1, TryInit
    } nextState = DrawStage;

    static uint32_t capturedTime = 0;
    static uint8_t tryInitCount = 1;

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case DrawStage:
                Serial.println("DrawStage");
                screen.drawProgress(LoadingProgress::STAGE_5);
                capturedTime = millis();
                nextState = TryInit;
                eventBuffer.push(Event::InitCCS811);
                break;
            case TryInit:
                Serial.println("TryInit");
                if (millis() - capturedTime < tryInitCount * 100) { // Pause 100..200..300..
                    eventBuffer.push(Event::InitCCS811);
                } else {
                    if (ccs811.begin() == ERR_OK) {
                        ccs811.setMeasurementMode(DFRobot_CCS811::eCycle_60s);
//                        /**
//                         * Set environment parameter
//                         * temperature Set temperature, unit:℃, range: -40~85℃
//                         * humidity    Set humidity, unit:RH, range: 0~100RH
//                         */
//                        ccs811.setInTempHum(/*temperature=*/25,/*humidity=*/50);
//                        ccs811.writeBaseLine(0x447B);
                        screen.drawProgressOk();
                        finishCallback();
                    } else if (tryInitCount == INIT_MAX_TRY_COUNT) {
                        screen.drawProgressFail();
                        finishCallback();
                    } else {
//                        screen.drawProgressDot(); // Bug - display stops drawing anything
                        tryInitCount++;
                        capturedTime = millis();
                        nextState = TryInit;
                        eventBuffer.push(Event::InitCCS811);
                    }
                }
                break;
            default:
                Serial.println("__UNKNOWN__");
                finishCallback();
                break;
        }
    }
}
