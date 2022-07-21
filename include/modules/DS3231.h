//
// Created by liosha on 24.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_DS3231_H
#define AIR_QUALITY_CLOCK_DS3231_H

#include "RTClib.h"

class DS3231 {
public:

    explicit DS3231();

    /**
     * Initializes pins
     */
    bool init();

    DateTime readDateTime() const;

    void updateDateTime(bool);

    static String formatDateAsString(DateTime &dateTime);

    static String formatTimeAsString(DateTime &dateTime);

private:

    RTC_DS3231 _rtc;
};


#endif //AIR_QUALITY_CLOCK_DS3231_H
