//
// Created by liosha on 23.05.2022.
//

#include "modules/MHZ19.h"

MHZ19::MHZ19() : _pinTx(0), _pinRx(0) {
}

bool MHZ19::init(uint8_t pinTx, uint8_t pinRx) {
    _pinTx = pinTx;
    _pinRx = pinRx;
    if (_mhz19.getStatus() <= 0) {
        _mhz19.begin(_pinTx, _pinRx);
        _mhz19.setAutoCalibration(false);
        return true;
    }
    return false;
}

int16_t MHZ19::readCo2() {
    int16_t co2 = _mhz19.getPPM();

    Serial.print("MHZ19: co2 = ");
    Serial.println(co2);

    return co2;
}