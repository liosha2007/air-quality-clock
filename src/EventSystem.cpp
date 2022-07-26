//
// Created by liosha on 19.07.2022.
//

#include "EventSystem.h"

void dispatchEvent(Event event) {
    Serial.print(".");
    switch (event) {
        case Event::InitLed:
            Serial.println("InitLed");
            led::init();
            break;
        case Event::InitScreen:
            Serial.println("InitScreen");
            st7735::init([]() {
                eventBuffer.push(Event::CleanScreen);
                eventBuffer.push(Event::InitMHZ19);
            });
            break;
        case Event::InitBeep:
            Serial.println("InitBeep");
//            beep_init::clean();
            break;
        case Event::InitBattery:
//            Serial.println("InitBattery");
//            battery::init([]() {
            battery::it.init(PIN_BUTTERY_LEVEL);
//            });
            break;
        case Event::CleanScreen:
            Serial.println("CleanArea");
            st7735::clean([]() {
            });
            break;
        case Event::InitMHZ19:
            Serial.println("InitMHZ19");
            mhz19::init([]() {
                eventBuffer.push(Event::InitBME280);
            });
            break;
        case Event::InitBME280:
            Serial.println("InitBME280");
            bme280::init([]() {
                eventBuffer.push(Event::InitDS3231);
            });
            break;
        case Event::InitDS3231:
            Serial.println("InitDS3231");
            ds3231::init([]() {
                eventBuffer.push(Event::InitMP503);
            });
            break;
        case Event::InitMP503:
            Serial.println("InitMP503");
            mp503::init([]() {
                eventBuffer.push(Event::InitCCS811);
            });
            break;
        case Event::InitCCS811:
            Serial.println("InitCCS811");
            ccs811::init([]() {
                eventBuffer.push(Event::CleanScreen);

                eventBuffer.push(Event::DrawBattery);
                eventBuffer.push(Event::DrawDateTime);
//                eventBuffer.push(Event::DrawMHZ19);
                eventBuffer.push(Event::DrawBME280);
//                eventBuffer.push(Event::DrawMP503);
//                eventBuffer.push(Event::DrawCCS811);
            });
            break;
        case Event::DrawBattery:
            Serial.println("DrawBattery");
            battery::draw();
            break;
        case Event::DrawDateTime:
            Serial.println("DrawDateTime");
            ds3231::draw();
            break;
//        case Event::DrawMHZ19:
//            Serial.println("DrawMHZ19");
//            mhz19::draw();
//            break;
        case Event::DrawBME280:
            Serial.println("DrawBME280");
            bme280::draw();
            break;
//        case Event::DrawMP503:
//            Serial.println("DrawMP503");
////            mp503::draw(); // Bug...
//            break;
//        case Event::DrawCCS811:
//            Serial.println("DrawCCS811");
//            ccs811::draw();
//            break;
        default:
            Serial.println("__UNKNOWN__");
            break;
    }
}
