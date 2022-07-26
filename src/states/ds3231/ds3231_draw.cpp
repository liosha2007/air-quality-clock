//
// Created by liosha on 20.07.2022.
//

#include "states/ds3231/ds3231_draw.h"

namespace ds3231 {

    enum : uint8_t {
        CleanArea = 1, DrawDots, Draw, Wait
    } nextState = CleanArea;

    static uint32_t capturedTime = 0;
    static bool isShowDots = false;
    static char dateString[11] = {0};
    static char timeString[6] = {0};

    void draw() {
        Serial.print("..");
        switch (nextState) {
            case CleanArea:
                Serial.println("CleanArea");

                // Clean date
                st7735::it.setCursor(DS3231_DRAW_DATE_X, DS3231_DRAW_DATE_Y);
                st7735::it.setTextSize(DS3231_DRAW_DATE_TEXT_SIZE);
                st7735::it.setTextColor(SCREEN_BACKGROUND);
                st7735::it.println(dateString);

                // Clean time
                st7735::it.setCursor(DS3231_DRAW_TIME_X, DS3231_DRAW_TIME_Y);
                st7735::it.setTextSize(DS3231_DRAW_TIME_TEXT_SIZE);
                st7735::it.setTextColor(SCREEN_BACKGROUND);
                st7735::it.println(timeString);

                nextState = Draw;
                eventBuffer.push(Event::DrawDateTime);
                break;
            case DrawDots:
                Serial.println("DrawDots");

//                st7735.drawDateTimeSeparator(isShowDots);
                isShowDots = !isShowDots;

                nextState = Wait;
                eventBuffer.push(Event::DrawDateTime);
                break;
            case Draw: {
                Serial.println("Draw");

                bool century = false;
                bool h12Flag = false;
                bool pmFlag = false;

                uint8_t day = it.getDate(), month = it.getMonth(century), year = it.getYear();
                uint8_t hour = it.getHour(h12Flag, pmFlag), minute = it.getMinute();

                sprintf(
                        dateString,
                        "%02hhu.%02hhu.20%02hhu",
                        day, month, year
                );

                // Draw date
                st7735::it.setCursor(DS3231_DRAW_DATE_X, DS3231_DRAW_DATE_Y);
                st7735::it.setTextSize(DS3231_DRAW_DATE_TEXT_SIZE);
                st7735::it.setTextColor(DS3231_DRAW_DATETIME_COLOR);
                st7735::it.println(dateString);

                sprintf(
                        timeString,
                        "%02hhu:%02hhu",
                        hour, minute
                );

                // Draw time
                st7735::it.setCursor(DS3231_DRAW_TIME_X, DS3231_DRAW_TIME_Y);
                st7735::it.setTextSize(DS3231_DRAW_TIME_TEXT_SIZE);
                st7735::it.setTextColor(DS3231_DRAW_DATETIME_COLOR);
                st7735::it.println(timeString);

                capturedTime = millis();
                nextState = Wait;
                eventBuffer.push(Event::DrawDateTime);
                break;
            }
            case Wait: {
                Serial.println("Wait");
                uint32_t ms = millis();
                if (ms - capturedTime < DS3231_DRAW_DELAY_MS) {
                    eventBuffer.push(Event::DrawDateTime);
                } else {
                    nextState = CleanArea;
                    eventBuffer.push(Event::DrawDateTime);
                }
                break;
            }
            default:
                Serial.println("__UNKNOWN__");
                break;
        }
    }
}