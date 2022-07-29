//
// Created by liosha on 20.07.2022.
//
#include "states/led/led_init.h"

namespace led {

    static State nextState = State::Init;
    static enum {
        Red = 1, Green, Blue, Disable
    } ledColor = Red;

    static uint32_t capturedTime = 0;

    void init() {
        IF_DEBUG(Serial.print("..");)
        switch (nextState) {
            case State::Init:
                IF_DEBUG(Serial.println("Init");)

                it.initialize(LED_RED, LED_GREEN, LED_BLUE);
                it.allOff();

                nextState = State::Draw;
                eventBuffer.push(Event::InitLed);
                break;
            case State::Draw: {
                IF_DEBUG(Serial.println("Draw");)

                switch (ledColor) {
                    case Red:
                        it.redOn();
                        ledColor = Green;
                        break;
                    case Green:
                        it.redOff();
                        it.greenOn();
                        ledColor = Blue;
                        break;
                    case Blue:
                        it.greenOff();
                        it.blueOn();
                        ledColor = Disable;
                        break;
                    case Disable:
                        it.blueOff();
                        return; // Leave led_init
                }
                capturedTime = millis();
                nextState = State::Delay;

                eventBuffer.push(Event::InitLed);
                break;
            }
            case State::Delay:
                IF_DEBUG(Serial.println("Delay");)
                if (millis() - capturedTime < 500) {
                    eventBuffer.push(Event::InitLed);
                } else {
                    nextState = State::Draw;
                    eventBuffer.push(Event::InitLed);
                }
                break;
            default:
                IF_DEBUG(Serial.println("__UNKNOWN__");)
                break;
        }
    }
}