#include "Utils.h"

uint16_t roundPressureQuality(float value) {
    return (uint16_t) value;
}

uint8_t roundHumanityQuality(float value) {
    return (uint8_t) value;
}

float roundTemperatureQuality(float value) {
    return (((float)((uint8_t)(value * 10))) / 10);
}

Quality detectCo2Quality(int16_t value) {
    if (value <= 400) {
        return Quality::GOOD;
    } else if (value <= 1000) {
        return Quality::NORMAL;
    } else if (value <= 1500) {
        return Quality::WARNING;
    } else if (value <= 2000) {
        return Quality::BAD;
    } else {
        return Quality::DANGEROUS;
    }
}

Quality detectPressureQuality(int16_t value) {
    // 0m over sea 641 - 760 - 816
    // ZP - 86m over sea, 649 - 768 - 824
    if (value >= 609 && value < 679) {
        return Quality::BAD;
    } else if (value >= 679 && value < 709) {
        return Quality::WARNING;
    } else if (value >= 709 && value < 739) {
        return Quality::NORMAL;
    } else if (value >= 739 && value < 797) {
        return Quality::GOOD;
    } else if (value >= 797 && value < 827) {
        return Quality::NORMAL;
    } else if (value >= 827 && value < 857) {
        return Quality::WARNING;
    } else if (value >= 857 && value < 927) {
        return Quality::BAD;
    } else {
        return Quality::DANGEROUS;
    }
}

Quality detectHumanityQuality(uint8_t value) {
    // 40-60 is ok, 25-40 and 60-75 so so
    if (value >= 10 && value < 25) {
        return Quality::BAD;
    }
    if (value >= 25 && value < 40) {
        return Quality::WARNING;
    } else if (value >= 40 && value <= 60) {
        return Quality::GOOD;
    } else if (value >= 60 && value < 75) {
        return Quality::WARNING;
    } else if (value >= 75 && value < 90) {
        return Quality::BAD;
    } else {
        return Quality::DANGEROUS;
    }
}

Quality detectTemperatureQuality(float value) {
    // 24 is ok, +-2
    if (value >= 12 && value < 18) {
        return Quality::BAD;
    } else if (value >= 18 && value < 22) {
        return Quality::WARNING;
    } else if (value >= 22 && value < 27) {
        return Quality::GOOD;
    } else if (value >= 27 && value < 30) {
        return Quality::WARNING;
    } else if (value >= 30 && value < 35) {
        return Quality::BAD;
    } else {
        return Quality::DANGEROUS;
    }
}
