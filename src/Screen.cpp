//
// Created by liosha on 04.01.2022.
//


#include "Screen.h"
#include "RTClib.h"
#include "DS3231.h"

Screen::Screen() {
    screenEnabled = true;
}

void Screen::initialize() {
    Serial.print("Screen initialization..");
    tft.init(); // It enables SS pin (D10 == PB2 == PCINT2)
    tft.setRotation(135);
    analogWrite(PCINT2, 0); // Disable
    delay(10);
    Serial.println("OK");
    tft.fillScreen(ST7735_BLACK);
    tft.setTextWrap(false);
}

void Screen::drawLogo() {
    tft.fillScreen(ST7735_BLACK);

    tft.setTextColor(ST7735_GREEN);
    tft.setCursor(25, 50);
    tft.setTextSize(2);
    tft.println("by liosha");
}

void Screen::drawProgress(LoadingProgress value) {
    if (value == LoadingProgress::STAGE_1) {
        Serial.print(F("MHZ-19..."));
        tft.fillScreen(ST7735_BLACK);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(3, currentY);
        tft.print("MHZ-19...");
        currentY += LINE_HEIGHT_SMALL;
    } else if (value == LoadingProgress::STAGE_2) {
        Serial.print(F("BME280..."));
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(3, currentY);
        tft.print("BME280...");
        currentY += LINE_HEIGHT_SMALL;
    } else if (value == LoadingProgress::STAGE_3) {
        Serial.print(F("DS3231..."));
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(3, currentY);
        tft.print("DS3231...");
        currentY += LINE_HEIGHT_SMALL;
    } else if (value == LoadingProgress::STAGE_4) {
        Serial.print(F("MP503..."));
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(3, currentY);
        tft.print("MP503...");
        currentY += LINE_HEIGHT_SMALL;
    } else if (value == LoadingProgress::STAGE_5) {
        Serial.print(F("CCS811..."));
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(3, currentY);
        tft.print("CCS811...");
        currentY += LINE_HEIGHT_SMALL;
    }
}

void Screen::drawProgressDot() {
    Serial.print(F("."));
    tft.print(".");
}

void Screen::drawProgressOk() {
    Serial.println(F(" OK"));
    tft.println(" OK");
}

void Screen::drawProgressFail() {
    Serial.println(F(" FAIL"));
    tft.println(" FAIL");
}

void Screen::cleanScreen() {
    tft.fillScreen(ST7735_BLACK);
    currentY = 3;
}

void Screen::drawButtery(uint16_t value, uint16_t min, uint16_t max) {
    if (currentButtery != value) {
        currentButtery = value;
        tft.fillRect(BUTTERY_X, BUTTERY_Y, BUTTERY_W, BUTTERY_H, ST7735_BLACK);

        int16_t width = (value / min) * (BUTTERY_W / max);
        tft.fillRect(BUTTERY_X, BUTTERY_Y, width, BUTTERY_H, ST7735_CYAN);
    }
}

void Screen::drawDateTime(DateTime &value) {
    // Date
    if (lastDateTime.day() != value.day() || lastDateTime.month() != value.month() ||
        lastDateTime.year() != value.year()) {
        tft.fillRect(DATE_X, DATE_Y, DATE_W, DATE_H, ST7735_BLACK);

        tft.setCursor(DATE_X, DATE_Y);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.setTextColor(ST7735_WHITE);

        String dateString = DS3231::formatDateAsString(value);
        tft.println(dateString);
    }
    // Time
    if (lastDateTime.hour() != value.hour() || lastDateTime.minute() != value.minute()) {
        tft.fillRect(TIME_HOURS_X, TIME_Y, TIME_HOURS_W, TIME_H, ST7735_BLACK);
        tft.fillRect(TIME_MINUTES_X, TIME_Y, TIME_MINUTES_W, TIME_H, ST7735_BLACK);

        tft.setTextSize(TEXT_SIZE_BIG);
        tft.setTextColor(ST7735_WHITE);

        String hours = "";
        uint8_t hrs = value.hour();
        hours += String(hrs / 10);
        hours += String(hrs % 10);

        tft.setCursor(TIME_HOURS_X, TIME_Y);
        tft.print(hours);

        String minutes = "";
        uint8_t mins = value.minute();
        if (mins < 10) {
            minutes += "0";
        }
        minutes += mins;

        tft.setCursor(TIME_MINUTES_X, TIME_Y);
        tft.print(minutes);
    }

    uint16_t millis = value.millis();
    bool dateTimeSeparator;
    if (millis >= 0 && millis < 500) {
        dateTimeSeparator = false;
    } else {
        dateTimeSeparator = true;
    }

    if (lastDateTimeSeparator != dateTimeSeparator) {
        tft.fillRect(TIME_SEPARATOR_X, TIME_Y, TIME_SEPARATOR_W, TIME_H, ST7735_BLACK);

        if (dateTimeSeparator) {
            tft.setCursor(TIME_SEPARATOR_X, TIME_Y);
            tft.setTextSize(TEXT_SIZE_BIG);
            tft.setTextColor(ST7735_WHITE);
            tft.print(String(":"));
        }
        lastDateTimeSeparator = dateTimeSeparator;
    }

    lastDateTime = value;
}

void Screen::drawPollution(uint8_t value, uint8_t maximum) {
    if (lastPollution != value) {
        lastPollution = value;

        tft.fillRect(POLLUTION_X, POLLUTION_Y, POLLUTION_W, POLLUTION_H, ST7735_BLACK);
        tft.drawRect(POLLUTION_X, POLLUTION_Y, POLLUTION_W, POLLUTION_H, ST7735_WHITE);

        uint16_t color;
        uint16_t mapValue;
        if (maximum / value == maximum / 1) {
            color = ST7735_GREEN;
            mapValue = 1;
        } else if (maximum / value == maximum / 2) {
            color = ST7735_YELLOW;
            mapValue = 2;
        } else if (maximum / value == maximum / 4) {
            color = ST7735_ORANGE;
            mapValue = 3;
        } else { // maximum / 8
            color = ST7735_RED;
            mapValue = 4;
        }

        tft.setCursor(POLLUTION_X + 3, POLLUTION_Y - 10);
        tft.setTextColor(color);
        tft.setTextSize(1);
        tft.setTextFont(1);
        tft.print(String("pollution"));

        uint8_t width = map(mapValue, 1, 4, POLLUTION_W / 4, POLLUTION_W - 2);
        tft.fillRect(POLLUTION_X + 1, POLLUTION_Y + 1, width, POLLUTION_H - 2, color);
    }
}

void Screen::drawCO2(int16_t value) {
    if (lastCo2 != value) {
        lastCo2 = value;
        tft.fillRect(CO2_X + 20, CO2_Y, CO2_W, CO2_H, ST7735_BLACK);
        tft.setCursor(CO2_X + 20, CO2_Y);

        Quality quality = detectCo2Quality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.print(String(value));

        tft.setCursor(CO2_X, CO2_Y);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.print(String("co2"));
    }
}

void Screen::drawPressure(uint16_t value) {
    if (lastPres != value) {
        lastPres = value;
        tft.fillRect(PRES_X + 20, PRES_Y, PRES_W, PRES_H, ST7735_BLACK);

        tft.setCursor(PRES_X + 20, PRES_Y);

        Quality quality = detectPressureQuality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.print(String(value));

        tft.setCursor(PRES_X, PRES_Y);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.print(String("prs"));
    }
}

void Screen::drawHumidity(uint8_t value) {
    if (lastHum != value) {
        lastHum = value;

        tft.fillRect(HUM_X, HUM_Y, HUM_W, HUM_H, ST7735_BLACK);
        tft.drawRect(HUM_X, HUM_Y, HUM_W, HUM_H, ST7735_WHITE);

        uint16_t color;
        // 40-60 is ok, 25-40 and 60-75 so so
        if (value >= 25 && value < 40) {
            color = ST7735_YELLOW;
        } else if (value >= 40 && value <= 60) {
            color = ST7735_GREEN;
        } else if (value >= 60 && value < 75) {
            color = ST7735_YELLOW;
        } else if (value >= 75 && value < 90) {
            color = ST7735_ORANGE;
        } else {
            color = ST7735_RED;
        }

        tft.setCursor(HUM_X + 3, HUM_Y - 10);
        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.setTextFont(1);
        tft.print(String("humidity"));

        uint8_t width = map(value, 1, 100, HUM_W / 4, HUM_W - 2);
        tft.fillRect(HUM_X + 1, HUM_Y + 1, width, HUM_H - 2, color);
    }
}

void Screen::drawTemperature(float value) {
    if (lastTemp != value) {
        lastTemp = value;
        tft.fillRect(TEMP_X + 20, TEMP_Y, TEMP_W, TEMP_H, ST7735_BLACK);

        tft.setCursor(TEMP_X + 20, TEMP_Y);

        Quality quality = detectTemperatureQuality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.print(String(value, 1));

        tft.setCursor(TEMP_X, TEMP_Y);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.print(String("tmp"));
    }
}

uint16_t Screen::getColorForQuality(Quality quality) {
    uint16_t color = ST7735_WHITE;
    if (quality == Quality::GOOD) {
        color = ST7735_GREEN;
    } else if (quality == Quality::NORMAL) {
        color = ST7735_GREEN;
    } else if (quality == Quality::WARNING) {
        color = ST7735_YELLOW;
    } else if (quality == Quality::BAD) {
        color = ST7735_ORANGE;
    } else if (quality == Quality::DANGEROUS) {
        color = ST7735_RED;
    }
    return color;
}

void Screen::drawTVOC(uint16_t value) {
    if (lastTvoc != value) {
        lastTvoc = value;
        tft.fillRect(TVOC_X + 20, TVOC_Y, TVOC_W, TVOC_H, ST7735_BLACK);

        tft.setCursor(TVOC_X + 20, TVOC_Y);

//        Quality quality = detectHumidityQuality(value);
//        uint16_t color = getColorForQuality(quality);
//
//        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.print(String(value));

        tft.setCursor(TVOC_X, TVOC_Y);
        tft.setTextSize(TEXT_SIZE_SMALL);
        tft.print(String("tvc"));
    }

}

void Screen::toggle() {
//    if (screenEnabled) {
//        screenEnabled = false;
//        analogWrite(screenPin, 0);
//        Serial.println("Screen was disabled");
//    } else {
//        screenEnabled = true;
//        analogWrite(screenPin, 75);
//        Serial.println("Screen was enabled");
//        updateScreenBrightness();
//    }
}