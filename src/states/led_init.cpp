//
// Created by liosha on 20.07.2022.
//
#include "states/led_init.h"

namespace led_init {

    enum : uint8_t {
        Init = 1, RedOn, GreenOn, BlueOn, KeepOn
    } nextState = Init;

    static uint32_t capturedTime = 0;

    void init() {
        Serial.print("..");
        switch (nextState) {
            case Init:
                Serial.println("Init");

                led.initialize(LED_RED, LED_GREEN, LED_BLUE);
                led.allOff();

                capturedTime = millis();
                nextState = RedOn;
                eventBuffer.push(Event::InitLed);
                break;
            case RedOn:
                Serial.println("RedOn");

                led.redOn();

                capturedTime = millis();
                nextState = GreenOn;
                eventBuffer.push(Event::InitLed);
                break;
            case GreenOn:
                Serial.println("GreenOn");
                if (millis() - capturedTime < 500) {
                    eventBuffer.push(Event::InitLed);
                } else {

                    led.redOff();
                    led.greenOn();

                    capturedTime = millis();
                    nextState = BlueOn;
                    eventBuffer.push(Event::InitLed);
                }
                break;
            case BlueOn:
                Serial.println("BlueOn");
                if (millis() - capturedTime < 500) {
                    eventBuffer.push(Event::InitLed);
                } else {

                    led.greenOff();
                    led.blueOn();

                    capturedTime = millis();
                    nextState = KeepOn;
                    eventBuffer.push(Event::InitLed);
                }
                break;
            case KeepOn:
                Serial.println("KeepOn");
                if (millis() - capturedTime < 500) {
                    eventBuffer.push(Event::InitLed);
                } else {

                    led.blueOff();
                }
                break;
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}