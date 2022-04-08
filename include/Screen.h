//
// Created by liosha on 04.01.2022.
//

#ifndef AIR_QUALITY_CLOCK_SCREEN_H
#define AIR_QUALITY_CLOCK_SCREEN_H

#include <Arduino.h>

#include <TFT_ST7735.h>
#include <SPI.h>

#include "Utils.h"

typedef enum {
    STAGE_1 = (1),
    STAGE_2 = (2),
    STAGE_3 = (3),
    STAGE_4 = (4)
} LoadingProgress;

class Screen {
public:
    /**
     * Creates Screen object
     * @param screenBrightnessPin pin, which is connected to BLK (brightness) on screen
     * @param photoResistorPin pin, which is connected to to the middle point of photo resistor and changeable resistor
     */
    Screen(uint8_t screenBrightnessPin, uint8_t photoResistorPin);

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

    void drawDate(String);

    void drawTime(String);

    void drawCO2(int16_t);

    void drawPressure(int16_t);

    void drawHumanity(uint8_t);

    void drawTemperature(float);

    void toggle();

    void updateScreenBrightness();

private:
    TFT_ST7735 tft;
    static const uint8_t LINE_HEIGHT_SMALL = 12;
    static const uint8_t LINE_HEIGHT_BIG = 21;
    static const uint8_t TEXT_SIZE_SMALL = 1;
    static const uint8_t TEXT_SIZE_NORMAL = 2;
    static const uint8_t TEXT_SIZE_BIG = 3;

    static const uint8_t DATE_X = 6;
    static const uint8_t DATE_Y = 11;
    static const uint8_t DATE_W = 116;
    static const uint8_t DATE_H = 14;

    static const uint8_t TIME_X = 23;
    static const uint8_t TIME_Y = 42;
    static const uint8_t TIME_W = 87;
    static const uint8_t TIME_H = 21;

    static const uint8_t CO2_X_WIDE = 16;
    static const uint8_t CO2_X_THIN = 24;
    static const uint8_t CO2_Y = 75;
    static const uint8_t CO2_W = 94;
    static const uint8_t CO2_H = 14;

    static const uint8_t PRES_X = 24;
    static const uint8_t PRES_Y = 96;
    static const uint8_t PRES_W = 94;
    static const uint8_t PRES_H = 14;

    static const uint8_t HUM_X = 29;
    static const uint8_t HUM_Y = 117;
    static const uint8_t HUM_W = 94;
    static const uint8_t HUM_H = 14;

    static const uint8_t TEMP_X = 20;
    static const uint8_t TEMP_Y = 138;
    static const uint8_t TEMP_W = 94;
    static const uint8_t TEMP_H = 14;

    uint8_t screenPin;
    uint8_t photoPin;
    uint8_t screenEnabled;
    uint8_t currentY = 3;
    String lastDate = "";
    String lastTime = "";
    int16_t lastCo2 = 0;
    int16_t lastPres = 0;
    uint8_t lastHum = 0;
    float lastTemp = 0;
    uint16_t lastResistor = 0;
    uint16_t brightnessHistory[5] = {0, 0, 0, 0, 0};

    uint16_t getColorForQuality(Quality quality);
};

#endif //AIR_QUALITY_CLOCK_SCREEN_H
