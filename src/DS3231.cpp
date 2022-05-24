//
// Created by liosha on 24.05.2022.
//

#include "DS3231.h"

DS3231::DS3231() {
    _dateTime = nullptr;
}

bool DS3231::initialize(uint8_t triesCount, void (&callback)(uint8_t)) {
    uint8_t tryNumber = 0;
    while (tryNumber < triesCount) {
        if (_rtc.begin()) {
            updateDateTime(false);
            return true;
        }
        callback(tryNumber);
        tryNumber++;
    }
    return false;
}

DateTime DS3231::readDateTime(uint32_t currentMillis) {
    if ((currentMillis % UPDATE_DS3231) == 0 || _dateTime == nullptr /* Initial load */) {
        updateValues();

        Serial.print("New date value = ");
        Serial.print(formatDateAsString(*_dateTime));
        Serial.print(", time value = ");
        Serial.println(formatTimeAsString(*_dateTime));
    } else if ((currentMillis % 998) == 0) {
        _dateTime->setSecond(_dateTime->second() + 1); // Will be synchronized each UPDATE_DS3231 ms
    }
    return *_dateTime;
}

void DS3231::updateValues() {
    delete _dateTime;
    DateTime now = RTC_DS3231::now();
    _dateTime = new DateTime(now);
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

DS3231::~DS3231() {
    delete _dateTime;
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
    uint8_t secs = dateTime.second();
    if (hrs / 10 == 0) {
        time = "0";
    } else {
        time += String(hrs / 10);
    }
    time += String(hrs % 10);
    if (secs % 2 == 0) {
        time += ":";
    } else {
        time += " ";
    }
    time += String(mins / 10);
    time += String(mins % 10);
    // time += ":";
    // if (secs < 10) {
    //   time += "0";
    // }
    // time += String(secs);

    return time;
}
