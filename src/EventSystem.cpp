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
            screen_init::init();
            break;
        case Event::InitScreenFinish:
            eventBuffer.push(Event::InitMHZ19);
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
            mhz19_init::init();
            break;
        case Event::InitMHZ19Finish:
            eventBuffer.push(Event::InitBME280);
            break;
        case Event::InitBME280:
            Serial.println("InitBME280");
            bme280_init::init();
            break;
        case Event::InitBME280Finish:
            eventBuffer.push(Event::InitDS3231);
            break;
        case Event::InitDS3231:
            Serial.println("InitDS3231");
            ds3231_init::init();
            break;
        case Event::InitDS3231Finish:
            eventBuffer.push(Event::InitMP503);
            break;
        case Event::InitMP503:
            Serial.println("InitMP503");
            mp503_init::init();
            break;
        case Event::InitMP503Finish:
            eventBuffer.push(Event::InitCCS811);
            break;
        case Event::InitCCS811:
            Serial.println("InitCCS811");
            ccs811_init::init();
            break;
        case Event::InitCCS811Finish:
            eventBuffer.push(Event::DrawDateTime);
            break;
        case Event::DrawDateTime:
            Serial.println("DrawDateTime");
            ccs811_drawdatetime::draw();
            break;
        default:
            Serial.println("__UNKNOWN__");
            break;
    }
}
