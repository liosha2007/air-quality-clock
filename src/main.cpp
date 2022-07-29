
#include "main.h"

__attribute__((unused)) void setup() {
    IF_DEBUG(Serial.begin(9600);)
    eventBuffer.push(Event::InitLed);
    eventBuffer.push(Event::InitScreen);
    eventBuffer.push(Event::InitBeep);
    eventBuffer.push(Event::InitBattery);
}

__attribute__((unused)) void loop() {
    if (eventBuffer.hasEvents()) {

        IF_DEBUG(Serial.println();)
        IF_DEBUG(Serial.print("Processing event (queue: ");)
        IF_DEBUG(Serial.print(eventBuffer.eventCount());)
        IF_DEBUG(Serial.println(")...");)

        Event event = eventBuffer.pull();

        dispatchEvent(event);
    }
}