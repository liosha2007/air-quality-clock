//
// Created by liosha on 20.07.2022.
//

#include <SoftwareSerial.h>
#include "states/mhz19/mhz19_init.h"

namespace mhz19 {

    static State nextState = State::Draw;

    static SoftwareSerial softwareSerial(MHZ19B_TX, MHZ19B_RX);

    void printTextOnDisplay(const char *text, uint16_t textColor = SCREEN_COLOR_GREEN) {
        st7735::it.setTextSize(MHZ19_INIT_TEXT_SIZE);
        st7735::it.setTextColor(textColor);
        st7735::it.print(text);
    }

    void init(void (*finishCallback)()) {
        Serial.print("..");
        switch (nextState) {
            case State::Draw:
                Serial.println("DrawStage");

                st7735::it.setCursor(MHZ19_INIT_CURSOR_X, MHZ19_INIT_CURSOR_Y);
                printTextOnDisplay("MHZ-19...", SCREEN_COLOR_GREEN);

                nextState = State::Init;
                eventBuffer.push(Event::InitMHZ19);
                break;
            case State::Init:
                Serial.println("TryInit");

                softwareSerial.begin(MHZ19_SERIAL_SPEED);
                it.begin(&softwareSerial);
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