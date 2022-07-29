//
// Created by liosha on 20.07.2022.
//

#include "states/ccs811/ccs811_init.h"

namespace ccs811 {

    static State nextState = State::Draw;

    static uint32_t capturedTime = 0;
    static uint8_t tryInitCount = 1;

    void printTextOnDisplay(const char *text, uint16_t textColor = SCREEN_COLOR_GREEN) {
        st7735::it.setTextSize(CCS811_INIT_TEXT_SIZE);
        st7735::it.setTextColor(textColor);
        st7735::it.print(text);
    }

    void init(void (*finishCallback)()) {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::Draw:
                IF_DEBUG(Serial.println("DrawStage");)

                st7735::it.setCursor(CCS811_INIT_CURSOR_X, CCS811_INIT_CURSOR_Y);
                printTextOnDisplay("CCS811...");

                capturedTime = millis();
                nextState = State::Init;
                eventBuffer.push(Event::InitCCS811);
                break;
            case State::Init:
                IF_DEBUG(Serial.println("TryInit");)
                if (millis() - capturedTime < tryInitCount * 100) { // Pause 100..200..300..
                    eventBuffer.push(Event::InitCCS811);
                } else {
                    // Wire.begin()
                    if (it.begin()) {
                        // Print CCS811 versions
                        IF_DEBUG(Serial.print("CCS811: hardware    version: ");) IF_DEBUG(Serial.println(it.hardware_version(),HEX);)
                        IF_DEBUG(Serial.print("CCS811: bootloader  version: ");) IF_DEBUG(Serial.println(it.bootloader_version(),HEX);)
                        IF_DEBUG(Serial.print("CCS811: application version: ");) IF_DEBUG(Serial.println(it.application_version(),HEX);)

                        printTextOnDisplay(" OK");
                        finishCallback();
                    } else if (tryInitCount == CCS811_INIT_MAX_TRY_COUNT) {
                        printTextOnDisplay(" FAIL", SCREEN_COLOR_RED);
                        finishCallback();
                    } else {
                        printTextOnDisplay(".");
                        tryInitCount++;
                        capturedTime = millis();
                        eventBuffer.push(Event::InitCCS811);
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
