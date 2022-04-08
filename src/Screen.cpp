//
// Created by liosha on 04.01.2022.
//


#include "Screen.h"

Screen::Screen(uint8_t screenBrightnessPin, uint8_t photoResistorPin) {
    screenPin = screenBrightnessPin;
    photoPin = photoResistorPin;
    screenEnabled = true;
}

void Screen::initialize() {
    Serial.print("Screen initialization..");
    tft.init(); // It enables SS pin (D10 == PB2 == PCINT2)
    analogWrite(PCINT2, 0); // Disable
    delay(10);
    Serial.println("OK");
    tft.fillScreen(ST7735_BLACK);
    tft.setTextWrap(false);
}

void Screen::drawLogo() {
    tft.fillScreen(ST7735_BLACK);

    tft.setTextColor(ST7735_GREEN);
    tft.setCursor(10, 65);
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

void Screen::drawDate(String value) {
    if (lastDate != value) {
        lastDate = value;
        tft.fillRect(DATE_X, DATE_Y, DATE_W, DATE_H, ST7735_BLACK);

        tft.setCursor(DATE_X, DATE_Y);
        tft.setTextColor(ST7735_WHITE);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.println(value);
    }
}

void Screen::drawTime(String value) {
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(TEXT_SIZE_BIG);
    if (lastTime.substring(0, 2) != value.substring(0, 2) || lastTime.substring(3, 5) != value.substring(3, 5)) {
        tft.fillRect(TIME_X, TIME_Y, TIME_W, TIME_H, ST7735_BLACK);

        tft.setCursor(TIME_X, TIME_Y);
        tft.println(value);
    } else {
        tft.setCursor(TIME_X + 36, TIME_Y);
        if (value.indexOf(":") == -1) {
            tft.fillRect(TIME_X + 42, TIME_Y, 3, TIME_H, ST7735_BLACK);
        } else {
            tft.print(":");
        }
    }
    lastTime = value;
}

void Screen::drawCO2(int16_t value) {
    if (lastCo2 != value) {
        lastCo2 = value;
        tft.fillRect(CO2_X_WIDE, CO2_Y, CO2_W, CO2_H, ST7735_BLACK);

        if (value < 1000) {
            tft.setCursor(CO2_X_THIN, CO2_Y);
        } else {
            tft.setCursor(CO2_X_WIDE, CO2_Y);
        }

        Quality quality = detectCo2Quality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.println("CO2:" + String(value));
    }
}

void Screen::drawPressure(int16_t value) {
    if (lastPres != value) {
        lastPres = value;
        tft.fillRect(PRES_X, PRES_Y, PRES_W, PRES_H, ST7735_BLACK);

        tft.setCursor(PRES_X, PRES_Y);

        Quality quality = detectPressureQuality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.println("PRS:" + String(value));
    }
}

void Screen::drawHumanity(uint8_t value) {
    if (lastHum != value) {
        lastHum = value;
        tft.fillRect(HUM_X, HUM_Y, HUM_W, HUM_H, ST7735_BLACK);

        tft.setCursor(HUM_X, HUM_Y);

        Quality quality = detectHumanityQuality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.println("HUM:" + String(value) + "%");
    }
}

void Screen::drawTemperature(float value) {
    if (lastTemp != value) {
        lastTemp = value;
        tft.fillRect(TEMP_X, TEMP_Y, TEMP_W, TEMP_H, ST7735_BLACK);

        tft.setCursor(TEMP_X, TEMP_Y);

        Quality quality = detectTemperatureQuality(value);
        uint16_t color = getColorForQuality(quality);

        tft.setTextColor(color);
        tft.setTextSize(TEXT_SIZE_NORMAL);
        tft.println("TMP:" + String(value, 1));
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
    } else if (quality == Quality::BAD){
        color = ST7735_ORANGE;
    } else if (quality == Quality::DANGEROUS) {
        color = ST7735_RED;
    }
    return color;
}

void Screen::toggle() {
    if (screenEnabled) {
        screenEnabled = false;
        analogWrite(screenPin, 0);
        Serial.println("Screen was disabled");
    } else {
        screenEnabled = true;
        analogWrite(screenPin, 75);
        Serial.println("Screen was enabled");
        updateScreenBrightness();
    }
}

void Screen::updateScreenBrightness() {
    uint16_t resistorValue = analogRead(photoPin);
    // Average of last 5
    brightnessHistory[0] = brightnessHistory[1];
    brightnessHistory[1] = brightnessHistory[2];
    brightnessHistory[2] = brightnessHistory[3];
    brightnessHistory[3] = brightnessHistory[4];
    brightnessHistory[4] = resistorValue;
    resistorValue = (brightnessHistory[0] + brightnessHistory[1] + brightnessHistory[2] + brightnessHistory[3] + brightnessHistory[4]) / 3;

    if (lastResistor != resistorValue) {
        lastResistor = resistorValue;
        uint16_t screenBrightness = min(map(resistorValue, 0, 75, 2, 130), 150);
        Serial.println("New screen brightness is " + String(screenBrightness) + ", res value is " + String(resistorValue));
        analogWrite(screenPin, screenBrightness);
    }
}