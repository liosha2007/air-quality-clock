//
// Created by liosha on 24.05.2022.
//

#include "CCS811.h"

CCS811::CCS811() {
    _ccs = Keyestudio_CCS811();
    _co2 = 0;
    _tvoc = 0;
}

bool CCS811::initialize(uint8_t triesCount, void (&callback)(uint8_t)) {
    uint8_t tryNumber = 0;
    while (tryNumber < triesCount) {
        if (_ccs.begin() == ERR_OK) {
            // Configure interrupt thresholds
            _ccs.setMeasCycle(_ccs.eCycle_60s);
            _ccs.setMeasurementMode(0, 0, _ccs.eMode3);
            return true;
        }
        callback(tryNumber);
        tryNumber++;
        delay(10);
    }
    return false;
}

uint16_t CCS811::readCo2(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_CCS811) == 0 || _co2 == 0 /* Initial load */) {
        updateValues();

        Serial.print("New co2 value = ");
        Serial.println(_co2);
    }
    return _co2;

}

uint16_t CCS811::readTvoc(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_CCS811) == 0 || _tvoc == 0 /* Initial load */) {
        updateValues();

        Serial.print("New tvoc value = ");
        Serial.println(_tvoc);
    }
    return _tvoc;
}

void CCS811::updateValues() {
    if (_ccs.checkDataReady()) {
        _co2 = _ccs.getCO2PPM();
        _tvoc = _ccs.getTVOCPPB();
    } else {
        Serial.println("CCS811 sensor is not ready\n\tsetting co2 or tvoc initial data as 1000");
    }
    if (_co2 == 0) {
        // The sensor gives first measurements only after few minutes
        // Update initial value to avoid spamming and request to sensor each loop iteration
        _co2 = 1000;
    }
    if (_tvoc == 0) {
        // The sensor gives first measurements only after few minutes
        // Update initial value to avoid spamming into serial and request to sensor each loop iteration
        _tvoc = 1000;
    }
}