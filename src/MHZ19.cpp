//
// Created by liosha on 23.05.2022.
//

#include "MHZ19.h"

MHZ19::MHZ19(uint8_t pinTx, uint8_t pinRx) {
    _pinTx = pinTx;
    _pinRx = pinRx;
    _co2 = 0;
}

bool MHZ19::initialize(uint8_t triesCount, void (&callback)(uint8_t)) {
    uint8_t tryNumber = 0;
    while (tryNumber < triesCount) {
        if (_mhz19.getStatus() <= 0) {
            _mhz19.begin(_pinTx, _pinRx);
            _mhz19.setAutoCalibration(false);
            return true;
        }
        callback(tryNumber);
        tryNumber++;
        delay(10);
    }
    return false;
}

int16_t MHZ19::readCo2(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_MHZ19) == 0 || _co2 == 0 /* Initial load */) {
        _co2 = _mhz19.getPPM();

        Serial.print("MHZ19: co2 = ");
        Serial.println(_co2);
    }
    return _co2;
}