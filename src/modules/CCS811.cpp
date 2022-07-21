//
// Created by liosha on 24.05.2022.
//

#include "modules/CCS811.h"

CCS811::CCS811() = default;

bool CCS811::init() {
    if (_ccs.begin() == ERR_OK) {
        // Configure interrupt thresholds
        _ccs.setMeasCycle(_ccs.eCycle_60s);
        _ccs.setMeasurementMode(0, 0, _ccs.eMode3);
        return true;
    }
    return false;
}

uint16_t CCS811::readCo2() {
    if (_ccs.checkDataReady()) {
        uint16_t co2 = _ccs.getCO2PPM();

        Serial.print("CCS811 co2 = ");
        Serial.println(co2);
        return co2;
    }
    return 0;
}

uint16_t CCS811::readTvoc() {
    if (_ccs.checkDataReady()) {
        uint16_t tvoc = _ccs.getTVOCPPB();

        Serial.print("CCS811 tvoc = ");
        Serial.println(tvoc);
        return tvoc;
    }
    return 0;
}