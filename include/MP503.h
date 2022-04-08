//
// Created by liosha on 05.01.2022.
// Gas sensor: formaldehyde, benzene, carbon monoxide, hydrogen, alcohol, ammonia, smoke of cigarette, essence &etc
// Working Current ≤60mA
// Warm-up Time ≤3 min
// Response Time ≤20s
// Recovery Time ≤60s
// Operating Temperature 0～50℃
//
// |  Pollution class  |  A output  |  B output  |  Air concentration    |
// -----------------------------------------------------------------------
// |  0                |  0V        |  0V        |  Clean air            |
// |  1                |  0V        |  +5V       |  Slight pollution air |
// |  2                |  +5V       |  0V        |  Middle pollution air |
// |  3                |  +5V       |  +5V       |  Heavy pollution air  |
//

#ifndef AIR_QUALITY_CLOCK_MP503_H
#define AIR_QUALITY_CLOCK_MP503_H

#include <Arduino.h>

class MP503 {
public:
    /**
     * Pin number
     */
    MP503(uint8_t, uint8_t);

    /**
     * Initializes pins
     */
    void initialize() const;

    /**
     * It is recommended (in datasheet) to delay for about 5 minute to let the sensor heat itself.
     * @return pollution level, see constants in MP503 class
     */
    uint8_t readPollution() const;

    static const uint8_t ERROR = 0;
    static const uint8_t CLEAN_AIR = 1;
    static const uint8_t SLIGHT_POLLUTION_AIR = 2;
    static const uint8_t MIDDLE_POLLUTION_AIR = 3;
    static const uint8_t HEAVY_POLLUTION_AIR = 4;

private:
    uint8_t _pinA;
    uint8_t _pinB;
};

#endif //AIR_QUALITY_CLOCK_MP503_H
