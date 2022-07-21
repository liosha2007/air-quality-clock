
//#include <avr/power.h>

#include "main.h"

//State nextState = State::Idle;

//void aqc_init_screen();

//void aqc_init_clock();

//__attribute__((unused)) void setup() {
//    nextState = State::InitScreen;
//}

//__attribute__((unused)) void loop() {
//    switch (nextState) {
//        case State::InitScreen:
//            aqc_init_screen();
//            break;
//        case State::InitDS3231:
//            aqc_init_clock();
//            break;
//    }
//}

//void aqc_init_clock() {
//    // region Time
//    screen.drawProgress(LoadingProgress::STAGE_3);
//    delay(50);
//    if (time.init(3, drawDotOnScreen)) {
//        screen.drawProgressOk();
//    } else {
//        screen.drawProgressFail();
//        delay(500);
//    }
//    // endregion
//}

//void aqc_init_screen() {
//    screen.init();
//    screen.drawLogo();
//
//    nextState = State::InitDS3231;
//}

__attribute__((unused)) void setup() {
    Serial.begin(9600);
    eventBuffer.push(Event::InitLed);
    eventBuffer.push(Event::InitScreen);
    eventBuffer.push(Event::InitBeep);
    eventBuffer.push(Event::InitBattery);
//    pinMode(LED_RED, OUTPUT);
//    pinMode(LED_GREEN, OUTPUT);
//    pinMode(LED_BLUE, OUTPUT);
//    analogWrite(LED_RED, 0);
//    analogWrite(LED_GREEN, 255);
//    analogWrite(LED_BLUE, 0);
}

__attribute__((unused)) void loop() {
    if (eventBuffer.hasEvents()) {

        Serial.println();
        Serial.print("Processing event (queue: ");
        Serial.print(eventBuffer.eventCount());
        Serial.println(")...");

        Event event = eventBuffer.pull();

        dispatchEvent(event);
    }
}