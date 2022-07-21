//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_MHZ19_H
#define AIR_QUALITY_CLOCK_MHZ19_H

#include <stdint.h>
#include "MHZ19_uart.h"

class MHZ19 {
public:
    /**
     * Pin numbers
     */
    explicit MHZ19();

    /**
     * Initializes pins
     */
    bool init(uint8_t, uint8_t);

    int16_t readCo2();

private:

    MHZ19_uart _mhz19;
    uint8_t _pinTx;
    uint8_t _pinRx;
};


#endif //AIR_QUALITY_CLOCK_MHZ19_H
