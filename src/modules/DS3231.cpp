//
// Created by liosha on 24.05.2022.
//

#include "modules/DS3231.h"

DS3231::DS3231() = default;

bool DS3231::init() {
    if (_rtc.begin()) {
        updateDateTime(false);
        return true;
    }
    return false;
}

DateTime DS3231::readDateTime() const {
    DateTime now = RTC_DS3231::now();
    return now;
}

/**
 * To update time, call it with true value, push to Arduino, change back to false and repush
 * Do not leave it with true
 * @param isForse force to update time using computer PC
 */
void DS3231::updateDateTime(bool isForse) {
    // TO UPDATE TIME, change to 1, push to Arduino, change back to 0 and repush
    if (isForse || _rtc.lostPower()) {
        RTC_DS3231::adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

String DS3231::formatDateAsString(DateTime &dateTime) {
    String date = "";
    if (dateTime.day() < 10) {
        date += "0";
    }
    date += String(dateTime.day());
    date += ".";
    if (dateTime.month() < 10) {
        date += "0";
    }
    date += String(dateTime.month());
    date += ".";
    date += String(dateTime.year());

    return date;
}

String DS3231::formatTimeAsString(DateTime &dateTime) {
    String time = "";
    uint8_t hrs = dateTime.hour();
    uint8_t mins = dateTime.minute();
    if (hrs / 10 == 0) {
        time = "0";
    } else {
        time += String(hrs / 10);
    }
    time += String(hrs % 10);
    time += ":";
    time += String(mins / 10);
    time += String(mins % 10);
    // time += ":";
    // if (secs < 10) {
    //   time += "0";
    // }
    // time += String(secs);

    return time;
}
