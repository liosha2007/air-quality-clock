#include <Arduino.h>
void setup() {
// write your initialization code here
    pinMode(13, OUTPUT);
}

void loop() {
// write your code here
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
}