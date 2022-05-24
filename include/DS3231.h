//
// Created by liosha on 24.05.2022.
//

#ifndef AIR_QUALITY_CLOCK_DS3231_H
#define AIR_QUALITY_CLOCK_DS3231_H

#include <RTClib.h>

#define UPDATE_DS3231 60000

class DS3231 {
public:

    explicit DS3231();

    /**
     * Initializes pins
     */
    bool initialize(uint8_t triesCount, void (&callback)(uint8_t));

    DateTime readDateTime(uint32_t currentMillis);

    void updateDateTime(bool);

    static String formatDateAsString(DateTime &dateTime);

    static String formatTimeAsString(DateTime &dateTime);

    ~DS3231();

private:
    void updateValues();

    RTC_DS3231 _rtc;
    DateTime *_dateTime;
};


#endif //AIR_QUALITY_CLOCK_DS3231_H
