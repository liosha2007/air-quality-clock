//
// Created by liosha on 23.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_MHZ19_H
#define AIR_QUALITY_CLOCK_MHZ19_H

#include <stdint.h>
#include <MHZ19_uart.h>

#define UPDATE_MHZ19 60000

class MHZ19 {
public:
    /**
     * Pin numbers
     */
    explicit MHZ19(uint8_t, uint8_t);

    /**
     * Initializes pins
     */
    bool initialize(uint8_t triesCount, void (&)(uint8_t));

    int16_t readCo2(uint32_t currentMillis);

private:

    MHZ19_uart _mhz19;
    uint8_t _pinTx;
    uint8_t _pinRx;
    int16_t _co2;
};


#endif //AIR_QUALITY_CLOCK_MHZ19_H
