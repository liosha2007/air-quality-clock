//
// Created by liosha on 19.07.2022.
//

#include "EventSystem.h"

void dispatchEvent(Event event) {
    IF_DEBUG(Serial.print(".");)
    switch (event) {
        case Event::InitLed:
            IF_DEBUG(Serial.println("InitLed");)
            led::init();
            break;
        case Event::InitScreen:
            IF_DEBUG(Serial.println("InitScreen");)
            st7735::init([]() {
                eventBuffer.push(Event::CleanScreen);
                eventBuffer.push(Event::InitMHZ19);
            });
            break;
        case Event::InitBeep:
            IF_DEBUG(Serial.println("InitBeep");)
//            beep_init::clean();
            break;
        case Event::InitBattery:
            IF_DEBUG(Serial.println("InitBattery");)
            battery::init([]() {
            });
            break;
        case Event::CleanScreen:
            IF_DEBUG(Serial.println("CleanArea");)
            st7735::clean([]() {
            });
            break;
        case Event::InitMHZ19:
            IF_DEBUG(Serial.println("InitMHZ19");)
            mhz19::init([]() {
                eventBuffer.push(Event::InitBME280);
            });
            break;
        case Event::InitBME280:
            IF_DEBUG(Serial.println("InitBME280");)
            bme280::init([]() {
                eventBuffer.push(Event::InitDS3231);
            });
            break;
        case Event::InitDS3231:
            IF_DEBUG(Serial.println("InitDS3231");)
            ds3231::init([]() {
                eventBuffer.push(Event::InitMP503);
            });
            break;
        case Event::InitMP503:
            IF_DEBUG(Serial.println("InitMP503");)
            mp503::init([]() {
                eventBuffer.push(Event::InitCCS811);
            });
            break;
        case Event::InitCCS811:
            IF_DEBUG(Serial.println("InitCCS811");)
            ccs811::init([]() {
                eventBuffer.push(Event::CleanScreen);

                eventBuffer.push(Event::DrawBattery);
                eventBuffer.push(Event::DrawDateTime);
                eventBuffer.push(Event::DrawMHZ19);
                eventBuffer.push(Event::DrawBME280);
//                eventBuffer.push(Event::DrawMP503);
//                eventBuffer.push(Event::DrawCCS811);
            });
            break;
        case Event::DrawBattery:
            IF_DEBUG(Serial.println("DrawBattery");)
            battery::draw();
            break;
        case Event::DrawDateTime:
            IF_DEBUG(Serial.println("DrawDateTime");)
            ds3231::draw();
            break;
        case Event::DrawMHZ19:
            IF_DEBUG(Serial.println("DrawMHZ19");)
            mhz19::draw();
            break;
        case Event::DrawBME280:
            IF_DEBUG(Serial.println("DrawBME280");)
            bme280::draw();
            break;
//        case Event::DrawMP503:
//            IF_DEBUG(Serial.println("DrawMP503");)
////            mp503::draw(); // Bug...
//            break;
//        case Event::DrawCCS811:
//            IF_DEBUG(Serial.println("DrawCCS811");)
//            ccs811::draw();
//            break;
        default:
            IF_DEBUG(Serial.println("__UNKNOWN__");)
            break;
    }
}
