
#include "main.h"

__attribute__((unused)) void setup() {
    Serial.begin(9600);
    eventBuffer.push(Event::InitLed);
    eventBuffer.push(Event::InitScreen);
    eventBuffer.push(Event::InitBeep);
    eventBuffer.push(Event::InitBattery);
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