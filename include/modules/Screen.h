//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_SCREEN_H
#define AIR_QUALITY_CLOCK_SCREEN_H

#include <Arduino.h>

#include "TFT_ST7735.h"
#include <SPI.h>

#include "Utils.h"
#include "RTClib.h"

typedef enum {
    STAGE_1 = (1),
    STAGE_2 = (2),
    STAGE_3 = (3),
    STAGE_4 = (4),
    STAGE_5 = (5)
} LoadingProgress;

class Screen {
public:

    Screen();

    /**
     * Initializes screen
     */
    void initialize();

    void drawLogo();

    void drawProgress(LoadingProgress);

    void drawProgressDot();

    void drawProgressOk();

    void drawProgressFail();

    void cleanScreen();

    void drawButtery(uint16_t, uint16_t, uint16_t);

    void drawDateTime(DateTime &);

    void drawTemperature(float);

    void drawHumidity(uint8_t);

    void drawPressure(uint16_t);

    void drawCO2(int16_t);

    void drawTVOC(uint16_t);

    void drawPollution(uint8_t, uint8_t);

    void toggle();

private:
    TFT_ST7735 tft;
    static const uint8_t LINE_HEIGHT_SMALL = 12;
    static const uint8_t LINE_HEIGHT_BIG = 21;
    static const uint8_t TEXT_SIZE_SMALL = 1;
    static const uint8_t TEXT_SIZE_NORMAL = 2;
    static const uint8_t TEXT_SIZE_BIG = 3;

    static const uint8_t BUTTERY_X = 1;
    static const uint8_t BUTTERY_Y = 1;
    static const uint8_t BUTTERY_W = 160;
    static const uint8_t BUTTERY_H = 3;

    static const uint8_t DATE_X = 20;
    static const uint8_t DATE_Y = 7;
    static const uint8_t DATE_W = 116;
    static const uint8_t DATE_H = 14;

    static const uint8_t TIME_HOURS_X = 35;
    static const uint8_t TIME_HOURS_W = 33;
    static const uint8_t TIME_SEPARATOR_X = TIME_HOURS_X + TIME_HOURS_W;
    static const uint8_t TIME_SEPARATOR_W = 15;
    static const uint8_t TIME_MINUTES_X = TIME_HOURS_X + TIME_HOURS_W + TIME_SEPARATOR_W;
    static const uint8_t TIME_Y = 28;
    static const uint8_t TIME_MINUTES_W = 33;
    static const uint8_t TIME_H = 21;

    static const uint8_t HUM_X = 2;
    static const uint8_t HUM_Y = 68;
    static const uint8_t HUM_W = 60;
    static const uint8_t HUM_H = 8;

    static const uint8_t TEMP_X = 2;
    static const uint8_t TEMP_Y = 85;
    static const uint8_t TEMP_W = 46;
    static const uint8_t TEMP_H = 14;

    static const uint8_t PRES_X = 2;
    static const uint8_t PRES_Y = 110;
    static const uint8_t PRES_W = 46;
    static const uint8_t PRES_H = 14;

    static const uint8_t POLLUTION_X = 100;
    static const uint8_t POLLUTION_Y = 68;
    static const uint8_t POLLUTION_W = 60;
    static const uint8_t POLLUTION_H = 8;

    static const uint8_t CO2_X = 92;
    static const uint8_t CO2_Y = 85;
    static const uint8_t CO2_W = 46;
    static const uint8_t CO2_H = 14;

    static const uint8_t TVOC_X = 92;
    static const uint8_t TVOC_Y = 110;
    static const uint8_t TVOC_W = 46;
    static const uint8_t TVOC_H = 14;

    uint8_t screenEnabled;
    uint8_t currentY = 3;
    uint8_t currentButtery = 0;
    DateTime lastDateTime;
    bool lastDateTimeSeparator = true;
    uint8_t lastPollution = 0;
    int16_t lastCo2 = 0;
    uint16_t lastPres = 0;
    uint8_t lastHum = 0;
    uint16_t lastTvoc = 0;
    float lastTemp = 0;

    uint16_t getColorForQuality(Quality quality);
};

#endif //AIR_QUALITY_CLOCK_SCREEN_H
