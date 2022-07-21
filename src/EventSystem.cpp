//
// Created by liosha on 19.07.2022.
//

#include "EventSystem.h"

void idleStateCallback() {
}


//struct StateTableRow {
//    State state;
//    Event event;
//    State nextState;
//    StateCallback callback;
//};
//
//struct StateTableRow StateTable[] = {
//        {State::Idle, Event::Init, State::InitScreen, idleStateCallback}
//};

void dispatchEvent(Event event) {
    Serial.print(".");
    switch (event) {
//        case Event::Init:
//            for (const auto &item: StateTable) {
//                if (item.state == nextState && item.event == event) {
//                    if (item.nextState != State::Idle) {
//                        nextState = item.nextState;
//                    }
//                    item.callback();
//                    break;
//                }
//            }
//            break;
        case Event::InitLed:
            Serial.println("InitLed");
            led_init::init();
            break;
        case Event::InitScreen:
            Serial.println("InitScreen");
            screen_init::init([]() {
                eventBuffer.push(Event::InitMHZ19);
            });
            break;
        case Event::InitBeep:
            Serial.println("InitBeep");
//            beep_init::init();
            break;
        case Event::InitBattery:
            Serial.println("InitBattery");
            battery_init::init();
            break;
        case Event::InitMHZ19:
            Serial.println("InitMHZ19");
            mhz19_init::init([]() {
                eventBuffer.push(Event::InitBME280);
            });
            break;
        case Event::InitBME280:
            Serial.println("InitBME280");
            bme280_init::init([]() {
                eventBuffer.push(Event::InitDS3231);
            });
            break;
        case Event::InitDS3231:
            Serial.println("InitDS3231");
            ds3231_init::init([]() {
                eventBuffer.push(Event::InitMP503);
            });
            break;
        case Event::InitMP503:
            Serial.println("InitMP503");
            mp503_init::init([]() {
                eventBuffer.push(Event::InitCCS811);
            });
            break;
        case Event::InitCCS811:
            Serial.println("InitCCS811");
            ccs811_init::init([]() {
                eventBuffer.push(Event::DrawDateTime);
                eventBuffer.push(Event::DrawMHZ19);
                eventBuffer.push(Event::DrawBME280);
                eventBuffer.push(Event::DrawMP503);
                eventBuffer.push(Event::DrawCCS811);
            });
            break;
        case Event::DrawDateTime:
            Serial.println("DrawDateTime");
            ds3231_drawdatetime::draw();
            break;
        case Event::DrawMHZ19:
            Serial.println("DrawMHZ19");
            mhz19_draw::draw();
            break;
        case Event::DrawBME280:
            Serial.println("DrawBME280");
            bme280_draw::draw();
            break;
        case Event::DrawMP503:
            Serial.println("DrawMP503");
//            mp503_draw::draw(); // Bug...
            break;
        case Event::DrawCCS811:
            Serial.println("DrawCCS811");
            ccs811_draw::draw();
            break;
        default:
            Serial.println("__UNKNOWN__");
            break;
    }
}
